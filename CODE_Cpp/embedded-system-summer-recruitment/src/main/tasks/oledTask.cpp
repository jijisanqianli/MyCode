#include "oledTask.h"
#include "TaskConfig.h"
#include "OledDisplayDriver.h"

void oledTask(void* param) {
    OledDisplayDriver* display = static_cast<OledDisplayDriver*>(param);

    for (;;) {
        // 阻塞等待: 有数据才醒来刷新, 平时睡觉不占 CPU
        SensorData_t data;
        if (xQueueReceive(oledQueue, &data, portMAX_DELAY)) {
            display->showSensors(data.temperature, data.humidity, data.soilPercent);
        }
    }
}
