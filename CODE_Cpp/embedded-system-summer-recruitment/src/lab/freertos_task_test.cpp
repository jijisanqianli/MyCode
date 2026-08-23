#include "common_config.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// ============================================================
// FreeRTOS 练手: 生产者/消费者 + 队列
//  - producerTask: 每 1s 往队列发一个递增数字
//  - consumerTask: 从队列收数字并打印(没数据就阻塞等待)
// 预期串口输出(交错属正常):
//   [P] send 0        [C] received 0
//   [P] send 1        [C] received 1
//   ...
// ============================================================

QueueHandle_t dataQueue;   // 队列句柄
int counter = 0;           // 生产者计数

// ---- 生产者任务: 每 1s 发一个数字 ----
void producerTask(void* param) {
    for (;;) {
        int value = counter++;                       // 生成数据
        xQueueSend(dataQueue, &value, 0);            // 放入队列(不等待)
        Serial.printf("[P] send %d\n", value);
        vTaskDelay(pdMS_TO_TICKS(1000));             // 阻塞 1s, 让出 CPU
    }
}

// ---- 消费者任务: 收数字并打印 ----
void consumerTask(void* param) {
    for (;;) {
        int value;
        // 阻塞等待: 队列有数据才返回, 没有就睡觉(不占 CPU)
        if (xQueueReceive(dataQueue, &value, portMAX_DELAY)) {
            Serial.printf("[C] received %d\n", value);
        }
    }
}

void setup() {
    Serial.begin(SYSTEM_BAUD_RATE);
    delay(1000);

    // 创建队列: 容量 5, 元素大小 int
    dataQueue = xQueueCreate(5, sizeof(int));

    // 创建两个任务: (函数, 名字, 栈字节, 参数, 优先级, 句柄, 核)
    xTaskCreatePinnedToCore(producerTask, "producer", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(consumerTask, "consumer", 2048, NULL, 1, NULL, 0);

    Serial.println("=== FreeRTOS task test started ===");
}

void loop() {
    // 主循环空转即可: 所有工作都交给上面的两个任务
    vTaskDelay(pdMS_TO_TICKS(1000));
}
