#include "TemperatureSensor.h"
#include "Config.h"

TemperatureSensorClass TemperatureSensor(TEMPERATURE_PIN);

TemperatureSensorClass::TemperatureSensorClass(uint8_t pin) :
    oneWire(pin),
    DS18B20(&oneWire)
{
}

void TemperatureSensorClass::begin()
{
    DS18B20.begin();
}

float TemperatureSensorClass::getCelcius()
{
    DS18B20.requestTemperatures();
    return DS18B20.getTempCByIndex(0);
}

