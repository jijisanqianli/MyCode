// 框架库在 src 显式 include, 让 LDF 检测到依赖
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "MqttDriver.h"
#include "MqttService.h"
#include "SensorService.h"
#include "IrrigationService.h"
#include "OledDisplayDriver.h"

// 仅用于编译验证 MqttService 模块(不实际连接 Broker)
static const uint8_t testPins[] = {1, 4, 8};
static const char* TEST_BROKER = "xxxx.emqxsl.cn";

IrrigationService testIrrigation(testPins, 3);
OledDisplayDriver testOled;
SensorService testSensors(47, 2, 3290, 1057, &testOled);
MqttDriver testMqtt(TEST_BROKER, 8883, "test-client", "user", "pass");
MqttService testMqttService(testMqtt, testSensors, testIrrigation,
                            "esp32-s3", "garden/esp32-s3/data", "garden/esp32-s3/cmd");

void setup() {
    Serial.begin(115200);

    testMqtt.begin();
    testMqttService.begin();

    Serial.println("MqttService compile & instantiate OK");
}

void loop() {
    testMqttService.update();
    delay(10);
}
