#include "MoistureSensor.h"
#include "Config.h"

MoistureSensorClass MoistureSensor(MOISTURE_PIN);

MoistureSensorClass::MoistureSensorClass(uint8_t pin) : 
    _pin(pin) 
{
}

void MoistureSensorClass::begin() 
{ 
    pinMode(_pin, INPUT); 
}

bool MoistureSensorClass::isMoist() 
{ 
    return ! digitalRead(_pin); 
}

