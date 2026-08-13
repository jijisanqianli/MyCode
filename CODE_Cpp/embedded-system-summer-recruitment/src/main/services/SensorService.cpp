#include "SensorService.h"

SensorService::SensorService(uint8_t dhtPin, uint8_t soilPin,
                             int soilDry, int soilWet,
                             OledDisplayDriver* display)
    : env(dhtPin), soil(soilPin, soilDry, soilWet), display(display) {}

void SensorService::begin() {
    env.begin();
    soil.begin();
}

void SensorService::update() {
    // 节流: 每 UPDATE_INTERVAL_MS 采样一轮
    uint32_t now = millis();
    if (now - lastUpdateMs < UPDATE_INTERVAL_MS) return;
    lastUpdateMs = now;

    env.read();      // EnvSensorDriver 内部已按 2s 节流
    soil.readRaw();  // 20 次采样取平均, 约 100ms 阻塞(2s 周期内可接受)

    if (display != nullptr) {
        display->showSensors(env.getTemperature(), env.getHumidity(),
                             soil.getMoisturePercent());
    }
}

bool SensorService::isEnvValid() const {
    return env.isValid();
}

float SensorService::getTemperature() const {
    return env.getTemperature();
}

float SensorService::getHumidity() const {
    return env.getHumidity();
}

int SensorService::getSoilPercent() const {
    return soil.getMoisturePercent();
}

String SensorService::getSensorsJson() const {
    String json = "{";
    if (env.isValid()) {
        json += "\"temperature\":" + String(env.getTemperature(), 1)
             + ",\"humidity\":" + String(env.getHumidity(), 1);
    } else {
        json += "\"temperature\":null,\"humidity\":null";
    }
    json += ",\"soil\":" + String(soil.getMoisturePercent());
    json += "}";
    return json;
}
