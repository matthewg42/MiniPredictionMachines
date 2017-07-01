#pragma once

#include <stdint.h>
#include <OneWire.h>
#include <DS18B20.h>

class TemperatureSensorClass {
public:
    TemperatureSensorClass(uint8_t pin);
    void begin();
    void request();
    bool ready();
    float getCelcius();

private:
    OneWire oneWire;
    DS18B20 sensor;
    uint8_t address[8];

    // Set the address of the device, or issue a warning
    bool findSensor();

};

extern TemperatureSensorClass TemperatureSensor;

