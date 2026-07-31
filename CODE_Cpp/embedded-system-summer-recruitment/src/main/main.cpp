#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    // 关键：死等 USB 串口在电脑端初始化完成（最多等 3 秒防止死锁）
    unsigned long start = millis();
    while (!Serial && (millis() - start < 3000)) {
        delay(10);
    }

    delay(500); // 稍微缓冲一下

    Serial.println("\n==========================================");
    Serial.println("Hello! ESP32-S3 USB Serial is Working!");
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("PSRAM Total Size: %d bytes (%.2f MB)\n",
                  ESP.getPsramSize(),
                  ESP.getPsramSize() / (1024.0 * 1024.0));
    Serial.println("==========================================");
}

void loop() {
    Serial.println("Board is running...");
    delay(2000);
}