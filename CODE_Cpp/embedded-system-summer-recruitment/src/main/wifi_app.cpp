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

// 非阻塞: 发起连接立即返回, WiFi 模块在后台自动连接, 状态由 wifi_is_connected() 轮询
bool connect_wifi_async(const char *ssid, const char *password) {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    // 降低发射功率(默认 19.5dBm → 11dBm), 减少 WiFi 峰值电流,
    // 缓解 USB 供电不足导致的掉线/复位(室内距离足够)
    WiFi.setTxPower(WIFI_POWER_11dBm);
    WiFi.begin(ssid, password);
    return true;
}

bool wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}

String wifi_get_ip() {
    return WiFi.localIP().toString();
}
