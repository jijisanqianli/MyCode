#include "wifi_app.h"

bool connect_wifi(const char *ssid,const char *password,uint16_t timeout_ms) {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    uint32_t start_time = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start_time < timeout_ms)) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    Serial.println("\nWiFi connection failed! (Timeout)");
    return false;
}
