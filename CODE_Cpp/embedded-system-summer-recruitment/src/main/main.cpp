#include "common_config.h"
#include "IrrigationService.h"
#include "WebServerController.h"
#include "OledDisplayDriver.h"
#include "SensorService.h"
#include "MqttDriver.h"
#include "MqttService.h"
// [任务化] 新增: 任务公共配置与任务入口
#include "TaskConfig.h"
#include "sensorTask.h"
#include "oledTask.h"
#include "controlTask.h"
#include "mqttTask.h"
#include "ConfigService.h"

//GPIO 引脚列表
static const uint8_t irrigationPins[] = {1, 4, 8};
static const size_t irrigationPinCount = sizeof(irrigationPins) / sizeof(irrigationPins[0]);

// 传感器引脚(与 lab 测试接线一致)
static const uint8_t DHT_PIN  = 47;  // DHT22 DATA
static const uint8_t SOIL_PIN = 2;   // HW-390 AO

// ===== [阶段B] MQTT 连接配置迁移到 ConfigService(/config.json), 原硬编码保留备查 =====
// static const char* MQTT_BROKER     = "i3daab3b.ala.cn-shenzhen.emqxsl.cn";
// static const uint16_t MQTT_PORT    = 8883;
// static const char* MQTT_USERNAME   = "esp32-s3";
// static const char* MQTT_PASSWORD   = "123654789";
static const char* MQTT_CLIENT_ID  = "esp32-s3-irrigation"; // 不能与 MQTTX 里已用的重复
static const char* MQTT_DEVICE_ID  = "esp32-s3";
static const char* MQTT_TOPIC_DATA = "garden/esp32-s3/data";   // 数据上报
static const char* MQTT_TOPIC_CMD  = "garden/esp32-s3/cmd";    // 指令下发
// =================================================================

// 配置服务(默认值见 ConfigService.h, 启动时读取 /config.json 覆盖)
ConfigService configService;

// 自动灌溉阈值(运行期变量, 默认 30/60, ConfigService 可覆盖)
volatile int autoIrrDryThreshold = 30;
volatile int autoIrrWetThreshold = 60;

IrrigationService irrigationService(irrigationPins, irrigationPinCount);
OledDisplayDriver oledDisplay;
// [阶段D] 历史数据服务(30s 降频, 环形缓冲 500 条)
HistoryService historyService;
// [任务化] OLED 显示改由 oledTask 驱动, SensorService 不再直接刷屏
// 原实现(未任务化时): SensorService sensorService(DHT_PIN, SOIL_PIN, 3290, 1057, &oledDisplay);
SensorService sensorService(DHT_PIN, SOIL_PIN, 3290, 1057, nullptr, &historyService);

WebServerController webServerController(80, irrigationService, sensorService, configService, historyService);

// 注意声明顺序: mqttService 依赖 mqttDriver/sensorService/irrigationService, 必须在其后声明
MqttDriver mqttDriver(configService.mqttBroker.c_str(), configService.mqttPort,
                      MQTT_CLIENT_ID, configService.mqttUsername.c_str(), configService.mqttPassword.c_str());
MqttService mqttService(mqttDriver, sensorService, irrigationService,
                        MQTT_DEVICE_ID, MQTT_TOPIC_DATA, MQTT_TOPIC_CMD);

// [任务化] 队列句柄定义(extern 声明在 TaskConfig.h, 此处为唯一分配点)
// 未创建的队列为 nullptr, 任务内已有判空保护
QueueHandle_t oledQueue         = nullptr;
QueueHandle_t latestDataQueue   = nullptr;
QueueHandle_t autoIrrQueue      = nullptr;
QueueHandle_t manualIrrQueue    = nullptr;

// 控制模式(extern 声明在 TaskConfig.h): controlTask 写, mqttTask/Web 读
volatile int8_t controlMode = MODE_AUTO;   // 默认自动模式

// sensorTask 参数包(数据源 + 灌溉控制, 供自动灌溉状态初始化/重置)
static SensorTaskParams sensorTaskParams = { &sensorService, &irrigationService };

void setup() {
    Serial.begin(115200);

    delay(1000);

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    // [阶段B] 读取持久化配置并应用(阈值/默认模式)
    configService.begin();
    autoIrrDryThreshold = configService.dryThreshold;
    autoIrrWetThreshold = configService.wetThreshold;
    if (configService.defaultMode == "manual") {
        controlMode = MODE_MANUAL;   // 配置指定默认手动模式
    }

    irrigationService.begin();
    sensorService.begin();

    if (oledDisplay.begin()) {
        oledDisplay.showBoot("Smart Irrigation", "System Ready");
    } else {
        Serial.println("OLED init failed");
    }

    // ===== [任务化 Step 2] 创建 oledQueue + 启动传感器/OLED 任务 =====
    // 状态型数据: 容量1 + xQueueOverwrite, 始终保留最新值
    oledQueue = xQueueCreate(1, sizeof(SensorData_t));

    xTaskCreatePinnedToCore(sensorTask, "sensor", TASK_STACK_SENSOR,
                            &sensorTaskParams, TASK_PRIO_SENSOR, NULL, TASK_CORE_SENSOR);
    xTaskCreatePinnedToCore(oledTask, "oled", TASK_STACK_OLED,
                            &oledDisplay, TASK_PRIO_OLED, NULL, TASK_CORE_OLED);

    // 非阻塞发起 WiFi 连接(SSID/密码来自持久化配置), 立即返回
    connect_wifi_async(configService.wifiSsid.c_str(), configService.wifiPassword.c_str());

    webServerController.begin();

    // [阶段B] 应用持久化配置中的 MQTT 连接参数(配置文件读取后可能覆盖默认值)
    mqttDriver.setConfig(configService.mqttBroker.c_str(), configService.mqttPort,
                         configService.mqttUsername.c_str(), configService.mqttPassword.c_str());
    mqttDriver.begin();
    mqttService.begin();   // MQTT 连接在 mqttTask 的 update() 中异步建立

    // ===== [任务化 Step 3/4] 其余队列 + 启动控制/MQTT 任务 =====
    latestDataQueue = xQueueCreate(1, sizeof(SensorData_t));   // 最新值, mqttTask peek
    autoIrrQueue    = xQueueCreate(1, sizeof(Command_t));      // 自动灌溉指令(状态变化才发)
    manualIrrQueue  = xQueueCreate(5, sizeof(Command_t));      // 事件型, 手动指令(不能丢)

    xTaskCreatePinnedToCore(controlTask, "control", TASK_STACK_CONTROL,
                            &irrigationService, TASK_PRIO_CONTROL, NULL, TASK_CORE_CONTROL);
    xTaskCreatePinnedToCore(mqttTask, "mqtt", TASK_STACK_MQTT,
                            &mqttService, TASK_PRIO_MQTT, NULL, TASK_CORE_MQTT);
}

void loop() {
    webServerController.handleClient();
    // [任务化] 传感器采样改由 sensorTask 驱动, MQTT 改由 mqttTask 驱动, 原调用保留备查:
    // sensorService.update();
    // mqttService.update();

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
