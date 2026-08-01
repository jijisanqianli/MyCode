#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_DRIVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_DRIVER_H
#include <Arduino.h>

class IrrigationDriver {
    uint8_t gpioPin;
public:
    explicit IrrigationDriver(uint8_t gpioPin);
    void init() const;
    void setState(bool on) const;
    uint8_t getGpioPin() const;
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_DRIVER_H
