// 框架库/第三方库在 src 显式 include, 让 LDF 检测到依赖
// (WiFiClientSecure 内部又依赖 WiFi 库, 需一并声明)
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "MqttDriver.h"

// 仅用于编译验证 MqttDriver 模块(不实际连接 Broker)
static const char* TEST_BROKER = "xxxx.emqxsl.cn";

// 模拟 Service 注册的业务回调
void onTestMessage(const String& topic, const String& payload) {
    Serial.printf("[TEST] topic=%s payload=%s\n", topic.c_str(), payload.c_str());
}

MqttDriver mqttDriver(TEST_BROKER, 8883, "test-client", "user", "pass");

void setup() {
    Serial.begin(115200);

    mqttDriver.begin();
    mqttDriver.setCallback(onTestMessage);

    Serial.println("MqttDriver compile & instantiate OK");
}

void loop() {
    delay(1000);
}
