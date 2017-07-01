#pragma once

#include <stdint.h>

class BatteryVoltageClass {
public:
    BatteryVoltageClass(uint8_t pin);
    void begin();
    float volts();

private:
    uint8_t _pin;

};

extern BatteryVoltageClass BatteryVoltage;
