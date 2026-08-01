#include "common_config.h"

//GPIO 引脚列表
static const uint8_t irrigationPins[] = {1, 4, 8};
static const size_t irrigationPinCount = sizeof(irrigationPins) / sizeof(irrigationPins[0]);

IrrigationService irrigationService(irrigationPins, irrigationPinCount);
WebServerController webServerController(80, irrigationService);

void setup() {
    Serial.begin(115200);

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    irrigationService.begin();

    connect_wifi("SDK","13730708827");

    webServerController.begin();
}

void loop() {
    webServerController.handleClient();
}
