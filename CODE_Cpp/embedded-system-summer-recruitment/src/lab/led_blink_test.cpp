#include "common_config.h"

const int ledPin = 4;  // LED 连接的引脚号

void setup() {
    // 将引脚初始化为输出模式
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);   
    delay(1000);
}
