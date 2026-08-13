#include "EnvSensorDriver.h"

EnvSensorDriver::EnvSensorDriver(uint8_t dataPin, uint8_t dhtType)
    : dht(dataPin, dhtType) {}

void EnvSensorDriver::begin() {
    dht.begin();
}

bool EnvSensorDriver::read() {
    // 节流: 距上次采样不足 2s 直接返回缓存状态, 不阻塞主循环
    uint32_t now = millis();
    if (now - lastReadMs < SAMPLE_INTERVAL_MS) {
        return isValid();
    }
    lastReadMs = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();   // 默认摄氏度
    if (isnan(h) || isnan(t)) {
        return false;
    }
    humidity    = h;
    temperature = t;
    return true;
}

float EnvSensorDriver::getTemperature() const {
    return temperature;
}

float EnvSensorDriver::getHumidity() const {
    return humidity;
}

bool EnvSensorDriver::isValid() const {
    return !isnan(temperature) && !isnan(humidity);
}

String EnvSensorDriver::toJson() const {
    if (!isValid()) {
        return "{\"temperature\":null,\"humidity\":null}";
    }
    return String("{\"temperature\":") + String(temperature, 1)
         + ",\"humidity\":" + String(humidity, 1) + "}";
}
