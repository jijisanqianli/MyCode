#include "common_config.h"

void setup() {
    // 在此处的代码会运行一次：
    Serial.begin(9600);  // 初始化串口通信，设置波特率为 9600
    while (!Serial){
        ; // 等待串口连接建立
    };
    Serial.println("Hello World!");  // 通过串口发送字符串 "Hello World!" 并换行
}

void loop() {
    Serial.println("Hello World!");
    delay(1000);
}