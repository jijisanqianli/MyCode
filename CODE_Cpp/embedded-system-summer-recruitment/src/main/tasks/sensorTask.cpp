#include "sensorTask.h"
#include "TaskConfig.h"
#include "SensorService.h"

// 自动灌溉判断由数据生产方(sensorTask)负责:
//  - 仅 AUTO 模式判断阈值(双阈值防抖)
//  - 状态变化才发指令 → controlTask 只在真正需要动作时被唤醒(消除冗余)
void sensorTask(void* param) {
    SensorTaskParams* params = static_cast<SensorTaskParams*>(param);
    SensorService* sensors    = params->sensors;
    IrrigationService* irrigation = params->irrigation;

    // 自动灌溉状态跟踪: 从【实际泵状态】起步(开机时泵可能在浇, 避免状态脱节)
    bool autoPumpState = irrigation->isIrrigating(0);
    int8_t lastMode    = controlMode;   // 模式变化检测(切回 AUTO 时重置状态)

    for (;;) {
        // ① 采样并更新 SensorService 缓存
        sensors->update();

        // 模式变化: 切回 AUTO 时, 状态跟踪重置为实际泵状态
        if (controlMode != lastMode) {
            lastMode = controlMode;
            if (controlMode == MODE_AUTO) {
                autoPumpState = irrigation->isIrrigating(0);
                Serial.printf("[SENSOR] mode -> AUTO, sync pump state = %s\n",
                              autoPumpState ? "ON" : "OFF");
            }
        }

        // ② 采样 + 打包(Service 内部完成, 短临界区保证一致性)
        // 原实现(逐个 getter 拼装, 已收敛到 Service):
        //   SensorData_t data;
        //   data.temperature = sensors->getTemperature();
        //   data.humidity    = sensors->getHumidity();
        //   data.soilPercent = sensors->getSoilPercent();
        //   data.timestamp   = millis();
        SensorData_t data = sensors->updateAndGet();

        // ③ 分发状态数据(容量1 + overwrite, 只留最新)
        if (oledQueue != nullptr) {
            xQueueOverwrite(oledQueue, &data);
        }
        if (latestDataQueue != nullptr) {
            xQueueOverwrite(latestDataQueue, &data);
        }

        // ④ 自动灌溉判断(AUTO 模式 + 状态变化才发指令)
        if (autoIrrQueue != nullptr && controlMode == MODE_AUTO) {
            bool wantPump = autoPumpState;   // 默认保持现状
            if (data.soilPercent < autoIrrDryThreshold) {
                wantPump = true;             // 干燥 → 开泵
            } else if (data.soilPercent > autoIrrWetThreshold) {
                wantPump = false;            // 湿润 → 关泵
            }
            // 中间区间(DRY~WET): 保持现状, 不发指令

            if (wantPump != autoPumpState) { // ★ 状态变化才唤醒 controlTask
                autoPumpState = wantPump;
                Command_t cmd;
                cmd.index  = 0;
                cmd.pumpOn = wantPump;
                cmd.mode   = -1;
                xQueueSend(autoIrrQueue, &cmd, 0);
                Serial.printf("[SENSOR] AUTO: soil %d%% -> pump %s\n",
                              data.soilPercent, wantPump ? "ON" : "OFF");
            }
        }

        // ⑤ 阻塞到下一个周期
        vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD_SENSOR));
    }
}
