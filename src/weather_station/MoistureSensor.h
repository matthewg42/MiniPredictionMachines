#pragma once

#include <stdint.h>

class MoistureSensorClass {
public:
    MoistureSensorClass(uint8_t pin);
    void begin();
    bool isMoist();

private:
    uint8_t _pin;

};

extern MoistureSensorClass MoistureSensor;

