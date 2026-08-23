#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_TASK_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_TASK_H

// oledTask: 核1 优先级1, 阻塞等待 oledQueue,
// 收到传感器数据即刷新 OLED(事件驱动, 无数据时睡觉不占 CPU)
// 参数: OledDisplayDriver*
void oledTask(void* param);

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_TASK_H
