#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H

#include "WiFi.h"

// 阻塞式: 原地等待直到连接成功或超时(适合 lab 测试/简单场景)
bool connect_wifi(const char *ssid, const char *password, uint16_t timeout_ms = 15000);

// 非阻塞式: 只发起连接立即返回, 系统继续跑其他功能,
// 在 loop() 中用 wifi_is_connected() / wifi_get_ip() 轮询状态(正式程序推荐)
bool connect_wifi_async(const char *ssid, const char *password);
bool wifi_is_connected();
String wifi_get_ip();

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H
