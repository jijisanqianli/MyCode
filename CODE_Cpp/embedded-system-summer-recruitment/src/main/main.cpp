#include "common_config.h"
#include "IrrigationService.h"
#include "WebServerController.h"
#include "OledDisplayDriver.h"
#include "SensorService.h"
#include "MqttDriver.h"
#include "MqttService.h"

//GPIO 引脚列表
static const uint8_t irrigationPins[] = {1, 4, 8};
static const size_t irrigationPinCount = sizeof(irrigationPins) / sizeof(irrigationPins[0]);

// 传感器引脚(与 lab 测试接线一致)
static const uint8_t DHT_PIN  = 47;  // DHT22 DATA
static const uint8_t SOIL_PIN = 2;   // HW-390 AO

// ===== MQTT 云端配置(EMQX Cloud Serverless, 填你自己的部署信息) =====
static const char* MQTT_BROKER     = "i3daab3b.ala.cn-shenzhen.emqxsl.cn";  // 部署详情页连接地址
static const uint16_t MQTT_PORT    = 8883;                  // MQTT over TLS
static const char* MQTT_CLIENT_ID  = "esp32-s3-irrigation"; // 不能与 MQTTX 里已用的重复
static const char* MQTT_USERNAME   = "esp32-s3";       // 部署认证用户名
static const char* MQTT_PASSWORD   = "123654789";       // 部署认证密码
static const char* MQTT_DEVICE_ID  = "esp32-s3";
static const char* MQTT_TOPIC_DATA = "garden/esp32-s3/data";   // 数据上报
static const char* MQTT_TOPIC_CMD  = "garden/esp32-s3/cmd";    // 指令下发
// =================================================================

IrrigationService irrigationService(irrigationPins, irrigationPinCount);
OledDisplayDriver oledDisplay;
SensorService sensorService(DHT_PIN, SOIL_PIN, 3290, 1057, &oledDisplay);

WebServerController webServerController(80, irrigationService, sensorService);

// 注意声明顺序: mqttService 依赖 mqttDriver/sensorService/irrigationService, 必须在其后声明
MqttDriver mqttDriver(MQTT_BROKER, MQTT_PORT, MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
MqttService mqttService(mqttDriver, sensorService, irrigationService,
                        MQTT_DEVICE_ID, MQTT_TOPIC_DATA, MQTT_TOPIC_CMD);

void setup() {
    Serial.begin(115200);

    delay(1000);

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    irrigationService.begin();
    sensorService.begin();

    if (oledDisplay.begin()) {
        oledDisplay.showBoot("Smart Irrigation", "System Ready");
    } else {
        Serial.println("OLED init failed");
    }

    // 非阻塞发起 WiFi 连接, 立即返回, 连接状态在 loop 心跳中查看
    connect_wifi_async("SDK","13730708827");

    webServerController.begin();

    mqttDriver.begin();
    mqttService.begin();   // MQTT 连接在 loop 的 update() 中异步建立
}

void loop() {
    webServerController.handleClient();
    sensorService.update();
    mqttService.update();   // MQTT: 重连 + 保活 + 5s 数据上报

    // 周期心跳输出: 确认程序存活 + WiFi 状态 + 传感器数据
    static uint32_t lastHeartbeatMs = 0;
    const uint32_t HEARTBEAT_INTERVAL_MS = 10000;
    uint32_t now = millis();
    if (now - lastHeartbeatMs >= HEARTBEAT_INTERVAL_MS) {
        lastHeartbeatMs = now;
        Serial.printf("[hb] WiFi:%d T:%.1f H:%.1f Soil:%d heap:%d",
                      WiFi.status(),
                      sensorService.getTemperature(),
                      sensorService.getHumidity(),
                      sensorService.getSoilPercent(),
                      ESP.getFreeHeap());
        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf(" IP:%s", WiFi.localIP().toString().c_str());
        }
        Serial.println();
    }
}
