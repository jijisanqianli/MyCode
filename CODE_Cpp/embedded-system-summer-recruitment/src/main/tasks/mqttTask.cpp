#include "mqttTask.h"
#include "TaskConfig.h"
#include "MqttService.h"

// mqttTask: 核0 优先级2
//  - mqttService.update(): 连接/重连/保活/收指令(回调 → 发 manualIrrQueue)
//  - 每 5s 从 latestDataQueue peek 最新数据 → publishData 上报(含 mode 字段)
void mqttTask(void* param) {
    MqttService* mqttService = static_cast<MqttService*>(param);

    uint32_t lastPublishMs = 0;
    for (;;) {
        // ① 连接管理 + 保活 + 收指令(内部有重连节流)
        mqttService->update();

        // ② 已连接且到上报周期 → 从单位置队列偷看最新数据并上报
        if (mqttService->isConnected() &&
            (millis() - lastPublishMs >= TASK_PERIOD_MQTT)) {
            lastPublishMs = millis();

            SensorData_t data;
            if (xQueuePeek(latestDataQueue, &data, 0)) {   // peek: 不消费, 只读最新
                mqttService->publishData(data);
            }
        }

        // 高频小延时: 保证 mqtt.loop 及时处理云端指令
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
