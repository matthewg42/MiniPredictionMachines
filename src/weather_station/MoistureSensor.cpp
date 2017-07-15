#include "MoistureSensor.h"
#include "Config.h"

MoistureSensorClass MoistureSensor(MOISTURE_PIN, GPS_CS_PIN);

MoistureSensorClass::MoistureSensorClass(uint8_t sensorPin, uint8_t powerPin) : 
    _sensorPin(sensorPin),
    _powerPin(powerPin) 
{
}

void MoistureSensorClass::begin() 
{ 
    pinMode(_sensorPin, INPUT); 
    pinMode(_powerPin, OUTPUT); 
    power(false);
}

bool MoistureSensorClass::isMoist() 
{ 
    return ! digitalRead(_sensorPin); 
}

void MoistureSensorClass::power(bool on)
{
    digitalWrite(_powerPin, on ? HIGH : LOW);
}

