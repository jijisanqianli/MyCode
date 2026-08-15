// 框架库在 src 显式 include, 让 LDF 检测到依赖(include/ 子目录头文件的库引用 LDF 追踪不到)
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "MqttService.h"

MqttService* MqttService::instance = nullptr;

MqttService::MqttService(MqttDriver& mqttDriver, SensorService& sensorService,
                         IrrigationService& irrigationService,
                         const char* deviceId, const char* topicData, const char* topicCmd)
    : mqttDriver(mqttDriver), sensorService(sensorService), irrigationService(irrigationService),
      topicData(topicData), topicCmd(topicCmd), deviceId(deviceId) {}

void MqttService::begin() {
    instance = this;
    // 把 MqttDriver 的"业务回调口子"接上本服务: 收到消息 → callbackBridge → onCommand
    mqttDriver.setCallback(MqttService::callbackBridge);
}

void MqttService::update() {
    uint32_t now = millis();

    // ① 连接管理: 未连接时定时重试(节流, 不阻塞主循环)
    if (!mqttDriver.isConnected()) {
        if (now - lastConnectMs >= CONNECT_RETRY_MS) {
            lastConnectMs = now;
            if (mqttDriver.connect()) {
                Serial.println("[MQTT] Broker connected");
                mqttDriver.subscribe(topicCmd);   // 连接成功后订阅控制主题(只做一次)
            } else {
                Serial.println("[MQTT] connect FAIL, retry later");
            }
        }
        return;
    }

    // ② 已连接: 保活 + 处理收到的消息(触发回调)
    mqttDriver.loop();

    // ③ 周期上报传感器数据
    if (now - lastPublishMs >= PUBLISH_INTERVAL_MS) {
        lastPublishMs = now;
        publishData();
    }
}

void MqttService::publishData() {
    // 在传感器 JSON 前加 device 字段: {"device":"esp32-s3","temperature":...}
    String payload = String("{\"device\":\"") + deviceId + "\","
                   + sensorService.getSensorsJson().substring(1);

    bool ok = mqttDriver.publish(topicData, payload.c_str());
    Serial.printf("[MQTT] publish %s -> %s\n", topicData, ok ? "OK" : "FAIL");
    if (ok) {
        Serial.println("  payload: " + payload);
    }
}

// 收到控制指令: {"pump":"on"/"off","index":N}, index 缺省时默认通道 0
void MqttService::onCommand(const String& topic, const String& payload) {
    Serial.printf("[MQTT] cmd received: %s -> %s\n", topic.c_str(), payload.c_str());

    if (payload.indexOf("\"pump\"") < 0) return;   // 非 pump 指令, 忽略

    // 解析通道 index: 从 "index":N 中提取数字, 缺省为 0
    size_t channelIndex = 0;
    int indexPos = payload.indexOf("\"index\"");
    if (indexPos >= 0) {
        int colonPos = payload.indexOf(':', indexPos);
        if (colonPos >= 0) {
            channelIndex = payload.substring(colonPos + 1).toInt();
        }
    }

    if (payload.indexOf("\"on\"") >= 0) {
        bool ok = irrigationService.turnOnIrrigation(channelIndex);
        Serial.printf("[MQTT] pump ON -> channel %u (%s)\n",
                      (unsigned)channelIndex, ok ? "OK" : "FAIL");
    } else if (payload.indexOf("\"off\"") >= 0) {
        bool ok = irrigationService.turnOffIrrigation(channelIndex);
        Serial.printf("[MQTT] pump OFF -> channel %u (%s)\n",
                      (unsigned)channelIndex, ok ? "OK" : "FAIL");
    }
}

// 桥接函数: MqttDriver 的 userCallback 指向这里, 再转给本对象处理
void MqttService::callbackBridge(const String& topic, const String& payload) {
    if (instance != nullptr) {
        instance->onCommand(topic, payload);
    }
}
