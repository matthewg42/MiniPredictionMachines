#pragma once

#include <stdint.h>

class MoistureSensorClass {
public:
    MoistureSensorClass(uint8_t sensorPin, uint8_t powerPin);
    // NOTE: device will be initialized, but powered OFF after begin()
    void begin();
    bool isMoist();
    void power(bool on);

private:
    uint8_t _sensorPin;
    uint8_t _powerPin;

};

extern MoistureSensorClass MoistureSensor;

