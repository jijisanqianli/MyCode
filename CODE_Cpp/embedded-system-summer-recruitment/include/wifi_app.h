#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H

#include "WiFi.h"

bool connect_wifi(const char *ssid, const char *password, uint16_t timeout_ms = 15000);

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WIFI_APP_H
