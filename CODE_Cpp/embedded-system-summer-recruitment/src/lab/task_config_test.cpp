#include "common_config.h"
#include "TaskConfig.h"

// 仅用于编译验证 TaskConfig.h(结构体布局/队列声明/任务声明)
void setup() {
    Serial.begin(SYSTEM_BAUD_RATE);
    delay(500);

    SensorData_t data = { 28.9f, 65.0f, 30, 0 };
    Command_t    cmd  = { 0, true };

    Serial.printf("SensorData_t size: %u bytes\n", (unsigned)sizeof(data));
    Serial.printf("Command_t size: %u bytes\n", (unsigned)sizeof(cmd));
    Serial.println("TaskConfig compile OK");
}

void loop() {
    delay(1000);
}
