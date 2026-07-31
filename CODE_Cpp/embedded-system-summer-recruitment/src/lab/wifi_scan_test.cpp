#include "common_config.h"
#include "WiFi.h"

void setup() {
    Serial.begin(115200);

    // 将 Wi-Fi 设置为站点模式，并断开任何已有的连接
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}
void loop() {
    Serial.println("Scan start");
    // WiFi.scanNetworks() 将返回找到的网络数量。
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");

    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // 打印找到的每个网络的 SSID 和 RSSI
            Serial.printf("%2d", i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4ld", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2ld", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN: Serial.print("open"); break;
                case WIFI_AUTH_WEP: Serial.print("WEP"); break;
                case WIFI_AUTH_WPA_PSK: Serial.print("WPA"); break;
                case WIFI_AUTH_WPA2_PSK: Serial.print("WPA2"); break;
                case WIFI_AUTH_WPA_WPA2_PSK: Serial.print("WPA+WPA2"); break;
                case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-EAP"); break;
                case WIFI_AUTH_WPA3_PSK: Serial.print("WPA3"); break;
                case WIFI_AUTH_WPA2_WPA3_PSK: Serial.print("WPA2+WPA3"); break;
                case WIFI_AUTH_WAPI_PSK: Serial.print("WAPI"); break;
                default: Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    // 删除扫描结果以释放内存
    WiFi.scanDelete();

    // 在再次扫描之前等待一下。
    delay(5000);
}