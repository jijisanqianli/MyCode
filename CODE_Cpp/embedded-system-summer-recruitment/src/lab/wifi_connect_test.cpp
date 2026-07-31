#include <WiFi.h>

// 请替换为你的 Wi-Fi 网络信息
const char *ssid = "SDK";
const char *password = "13730708827";

void setup() {
    Serial.begin(115200);

    delay(10);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}
