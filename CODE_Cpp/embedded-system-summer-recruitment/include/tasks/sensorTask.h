#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_TASK_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_TASK_H

#include "SensorService.h"
#include "IrrigationService.h"

// sensorTask 参数包: 数据源 + 控制目标(自动灌溉状态初始化/重置用)
struct SensorTaskParams {
    SensorService*     sensors;
    IrrigationService* irrigation;
};

// sensorTask: 核0 优先级2, 每 2s 采样传感器,
// 组装 SensorData_t 发到 oledQueue(OLED) 与 overwrite latestDataQueue(MQTT),
// AUTO 模式下做阈值判断, 状态变化才发指令到 autoIrrQueue
// 参数: SensorTaskParams*
void sensorTask(void* param);

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_TASK_H
