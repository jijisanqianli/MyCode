#include "common_config.h"
#include <Wire.h>

// 注意: 本板 Octal PSRAM(qio_opi)占用 GPIO33~37, 原 35/36 不能用作 I2C(会破坏 PSRAM)
#define SDA_PIN 9   // OLED SDA
#define SCL_PIN 10  // OLED SCL

//oled地址：0x3c
//温湿度

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN,SCL_PIN);
}

void loop() {
    byte error, address;
    int nDevices = 0;

    delay(5000);

    Serial.println("Scanning for I2C devices ...");
    for (address = 0x01; address < 0x7f; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.printf("I2C device found at address 0x%02X\n", address);
            nDevices++;
        } else if (error != 2) {
            Serial.printf("Error %d at address 0x%02X\n", error, address);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found");
    }
}