#pragma once

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensorClass {
public:
    TemperatureSensorClass(uint8_t pin);
    void begin();
    float getCelcius();

private:
    OneWire oneWire;
    DallasTemperature DS18B20;

};

extern TemperatureSensorClass TemperatureSensor;

