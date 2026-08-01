#include "WiFi.h"
#include "WebServer.h"
#include "LittleFS.h"

const char* ssid = "SDK";
const char* password = "13730708827";
WebServer server(80);

void handleRoot();

void setup() {
    Serial.begin(115200);

    unsigned long start = millis();
    while (!Serial && (millis() - start < 2500)) {
        delay(10);
    }
    // 2. 核心：串口握手后，额外给电脑串口缓冲区留出 500ms 的响应缓冲时间！
    delay(500);

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi successfully");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP Server started.");
}

void loop() {
    server.handleClient();
}

void handleRoot() {
    File file = LittleFS.open("/webserver_test.html", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "text/html");
    file.close();
}