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

    // ① 连接管理: 未连接时定时重试(节流, 不阻塞)
    if (!mqttDriver.isConnected()) {
        if (now - lastConnectMs >= CONNECT_RETRY_MS) {
            lastConnectMs = now;
            if (mqttDriver.connect()) {
                Serial.println("[MQTT] Broker connected");
                mqttDriver.subscribe(topicCmd);   // 连接成功后订阅控制主题
            } else {
                Serial.println("[MQTT] connect FAIL, retry later");
            }
        }
        return;
    }

    // ② 已连接: 保活 + 处理收到的消息(触发回调 → 发 manualIrrQueue)
    mqttDriver.loop();
    // (周期上报已改由 mqttTask 驱动, 此处不再上报)
}

bool MqttService::isConnected() {
    return mqttDriver.isConnected();
}

// 由 mqttTask 调用: 用最新一次采样的完整结构体拼 JSON(保证一致性), 含 mode 字段
void MqttService::publishData(const SensorData_t& data) {
    String payload = String("{\"device\":\"") + deviceId + "\""
        + ",\"temperature\":" + String(data.temperature, 1)
        + ",\"humidity\":" + String(data.humidity, 1)
        + ",\"soil\":" + String(data.soilPercent)
        + ",\"mode\":\"" + (controlMode == MODE_MANUAL ? "manual" : "auto") + "\"}";

    bool ok = mqttDriver.publish(topicData, payload.c_str());
    Serial.printf("[MQTT] publish %s -> %s\n", topicData, ok ? "OK" : "FAIL");
    if (ok) {
        Serial.println("  payload: " + payload);
    }
}

// 收到云端指令: 解析后发 manualIrrQueue(执行权收敛到 controlTask)
// {"pump":"on"/"off","index":N} 或 {"mode":"auto"/"manual"}
void MqttService::onCommand(const String& topic, const String& payload) {
    Serial.printf("[MQTT] cmd received: %s\n", payload.c_str());

    Command_t cmd;
    cmd.index  = 0;
    cmd.pumpOn = false;
    cmd.mode   = -1;   // 默认不切换模式

    if (payload.indexOf("\"mode\"") >= 0) {
        // 模式切换指令
        if (payload.indexOf("\"auto\"") >= 0) {
            cmd.mode = MODE_AUTO;
        } else if (payload.indexOf("\"manual\"") >= 0) {
            cmd.mode = MODE_MANUAL;
        } else {
            return;   // 无法识别
        }
    } else if (payload.indexOf("\"pump\"") >= 0) {
        // 手动开关指令
        cmd.pumpOn = (payload.indexOf("\"on\"") >= 0);
        int pos = payload.indexOf("\"index\"");
        if (pos >= 0) {
            int colon = payload.indexOf(':', pos);
            if (colon >= 0) {
                cmd.index = (uint8_t)payload.substring(colon + 1).toInt();
            }
        }
    } else {
        return;   // 非 pump 非 mode, 忽略
    }

    if (manualIrrQueue != nullptr) {
        xQueueSend(manualIrrQueue, &cmd, 0);
    }
}

// 桥接函数: MqttDriver 的 userCallback 指向这里, 再转给本对象处理
void MqttService::callbackBridge(const String& topic, const String& payload) {
    if (instance != nullptr) {
        instance->onCommand(topic, payload);
    }
}
