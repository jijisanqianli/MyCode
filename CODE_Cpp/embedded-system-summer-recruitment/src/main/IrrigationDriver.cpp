#include "IrrigationDriver.h"

IrrigationDriver::IrrigationDriver(uint8_t gpioPin): gpioPin(gpioPin) {}

void IrrigationDriver::init() const {
    pinMode(gpioPin, OUTPUT);
    digitalWrite(gpioPin, LOW);
}

void IrrigationDriver::setState(bool on) const {
    digitalWrite(gpioPin, on ? HIGH : LOW);
}

uint8_t IrrigationDriver::getGpioPin() const {
    return gpioPin;
}
