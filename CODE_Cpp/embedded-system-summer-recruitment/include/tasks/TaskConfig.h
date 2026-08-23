#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_TASK_CONFIG_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_TASK_CONFIG_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// ============================================================
// FreeRTOS 任务化改造 · 公共配置中枢
// 集中定义: 任务参数(优先级/核/栈) / 周期 / 跨任务数据结构 / 队列句柄
// ============================================================

// ---------- 任务参数 ----------
// 优先级: controlTask 最高(灌溉实时性), sensor/mqtt 中, oled/web 低
#define TASK_PRIO_SENSOR   2
#define TASK_PRIO_MQTT     2
#define TASK_PRIO_CONTROL  3
#define TASK_PRIO_OLED     1

// 核分配: 核0(协议/采样) 核1(控制/显示)
#define TASK_CORE_SENSOR   0
#define TASK_CORE_MQTT     0
#define TASK_CORE_CONTROL  1
#define TASK_CORE_OLED     1

// 任务栈大小(字节): 传值拷贝 SensorData_t 等用栈, 先给 4096
#define TASK_STACK_SENSOR  4096
#define TASK_STACK_MQTT    4096
#define TASK_STACK_CONTROL 4096
#define TASK_STACK_OLED    4096

// ---------- 周期(ms) ----------
#define TASK_PERIOD_SENSOR 2000   // 采样周期
#define TASK_PERIOD_MQTT   5000   // 数据上报周期

// ---------- 跨任务数据结构 ----------
// 传感器数据: 队列值拷贝传递(整个结构体一次拷贝, 保证同一次采样的一致性)
typedef struct {
    float    temperature;   // °C
    float    humidity;      // %
    int      soilPercent;   // 0~100
    uint32_t timestamp;     // 采样时刻(millis)
} SensorData_t;

// 灌溉控制指令: {"pump":"on"/"off","index":N} 或 {"mode":"auto"/"manual"}
typedef struct {
    uint8_t index;    // 通道索引
    bool    pumpOn;   // true=开泵, false=关泵
    int8_t  mode;     // -1=不切换模式, 0=自动, 1=手动(模式切换指令用)
} Command_t;

// 控制模式
#define MODE_AUTO   0
#define MODE_MANUAL 1
// 当前控制模式: controlTask 写, mqttTask/Web 读(单字节原子读写, volatile 足够)
extern volatile int8_t controlMode;

// 自动灌溉阈值(双阈值防抖): 土壤湿度 < DRY 开泵, > WET 关泵(可调)
#define AUTO_IRR_DRY_THRESHOLD   30   // 低于 30% 视为干燥, 开启灌溉
#define AUTO_IRR_WET_THRESHOLD   60   // 高于 60% 视为湿润, 停止灌溉

// ---------- 队列句柄(由 main.cpp 创建, 各任务 extern 使用) ----------
// 状态型队列(OLED/MQTT/自动灌溉): 容量1 + xQueueOverwrite, 始终保留最新一次采样
// 事件型队列(手动指令): 容量>1 + xQueueSend, 每条指令都要执行, 不能覆盖丢失
extern QueueHandle_t oledQueue;         // sensorTask overwrite → oledTask      (最新值, 显示)
extern QueueHandle_t latestDataQueue;   // sensorTask overwrite → mqttTask peek (最新值快照)
extern QueueHandle_t autoIrrQueue;      // sensorTask send → controlTask (自动灌溉指令 Command_t, 状态变化才发)
extern QueueHandle_t manualIrrQueue;    // mqttTask/Web send → controlTask      (事件指令, 每条都执行)

// ---------- 任务函数声明(实现在各 task.cpp) ----------
void sensorTask(void* param);
void mqttTask(void* param);
void controlTask(void* param);
void oledTask(void* param);

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_TASK_CONFIG_H
