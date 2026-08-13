#include "SoilSensorDriver.h"

SoilSensorDriver::SoilSensorDriver(uint8_t pin, int dry, int wet)
    : adcPin(pin), dryValue(dry), wetValue(wet) {}

void SoilSensorDriver::begin() {
    // 打开引脚衰减以覆盖 0~3.3V 全量程(否则读数会提前截顶)
    analogSetPinAttenuation(adcPin, ADC_11db);
    pinMode(adcPin, INPUT);
}

int SoilSensorDriver::readRaw() {
    long sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        sum += analogRead(adcPin);
        delay(5);
    }
    lastRaw = (int)(sum / SAMPLE_COUNT);
    return lastRaw;
}

int SoilSensorDriver::getMoisturePercent() const {
    if (lastRaw < 0) return -1;
    long span = (long)dryValue - wetValue;
    if (span <= 0) return -1;   // 标定值异常保护

    long pct = (long)(dryValue - lastRaw) * 100 / span;
    if (pct < 0)   return 0;
    if (pct > 100) return 100;
    return (int)pct;
}

int SoilSensorDriver::getLastRaw() const {
    return lastRaw;
}

String SoilSensorDriver::toJson() const {
    if (lastRaw < 0) {
        return "{\"soil\":null}";
    }
    return String("{\"soil\":") + getMoisturePercent() + "}";
}
