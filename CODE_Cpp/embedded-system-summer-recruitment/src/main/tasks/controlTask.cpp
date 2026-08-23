#include "controlTask.h"
#include "TaskConfig.h"
#include "IrrigationService.h"

// controlTask: 核1 优先级3(最高)
//  - 队列集同时等待: manualIrrQueue(手动指令) + autoIrrQueue(自动灌溉触发)
//  - 模式状态机: pump 指令自动切 MANUAL, 回 AUTO 需显式 {"mode":"auto"}
void controlTask(void* param) {
    IrrigationService* irrigation = static_cast<IrrigationService*>(param);

    // 队列集容量 = 各队列容量之和(autoIrrQueue:1 + manualIrrQueue:5)
    QueueSetHandle_t queueSet = xQueueCreateSet(6);
    xQueueAddToSet(autoIrrQueue, queueSet);
    xQueueAddToSet(manualIrrQueue, queueSet);

    for (;;) {
        // 阻塞等待任一队列有数据(事件驱动, 平时睡觉不占 CPU)
        QueueSetMemberHandle_t ready = xQueueSelectFromSet(queueSet, portMAX_DELAY);

        if (ready == manualIrrQueue) {
            // ===== 手动指令通道 =====
            Command_t cmd;
            if (xQueueReceive(manualIrrQueue, &cmd, 0)) {
                if (cmd.mode >= 0) {
                    // 模式切换指令 {"mode":"auto"/"manual"}
                    controlMode = cmd.mode;
                    Serial.printf("[CTRL] mode -> %s\n",
                                  controlMode == MODE_AUTO ? "AUTO" : "MANUAL");
                } else {
                    // 手动 pump 指令: 执行 + 自动切到手动模式(手动手动不冲突)
                    controlMode = MODE_MANUAL;
                    if (cmd.pumpOn) {
                        irrigation->turnOnIrrigation(cmd.index);
                    } else {
                        irrigation->turnOffIrrigation(cmd.index);
                    }
                    Serial.printf("[CTRL] pump %s -> channel %u (mode=MANUAL)\n",
                                  cmd.pumpOn ? "ON" : "OFF", cmd.index);
                }
            }
        } else if (ready == autoIrrQueue) {
            // ===== 自动灌溉指令(sensorTask 已做阈值判断, 此处确认模式后执行) =====
            Command_t cmd;
            if (xQueueReceive(autoIrrQueue, &cmd, 0)) {
                if (controlMode == MODE_AUTO) {   // 双保险: 防判断期间被切到手动
                    if (cmd.pumpOn) {
                        irrigation->turnOnIrrigation(cmd.index);
                    } else {
                        irrigation->turnOffIrrigation(cmd.index);
                    }
                    Serial.printf("[CTRL] AUTO: pump %s -> channel %u\n",
                                  cmd.pumpOn ? "ON" : "OFF", cmd.index);
                }
                // MANUAL 模式: 忽略自动灌溉指令
            }
        }
    }
}
