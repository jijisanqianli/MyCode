#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <Arduino.h>
#include "wifi_app.h"

// 全局波特率定义
#define SYSTEM_BAUD_RATE 115200

// 自定义的全局配置结构体或常用工具函数
inline void printSystemHeader(const char* moduleName) {
    Serial.printf("\n================ [ %s ] ================\n", moduleName);
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
    Serial.println("===========================================");
}

#endif // COMMON_CONFIG_H