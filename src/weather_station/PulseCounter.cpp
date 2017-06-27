#include "PulseCounter.h"
#include "Config.h"

PulseCounter::PulseCounter(uint8_t pin) : 
    _pin(pin)
{
    reset();
}

void PulseCounter::begin(uint8_t pinModeSetting) 
{ 
    pinMode(_pin, pinModeSetting); 
}

void PulseCounter::addPulse() 
{ 
    _pulseCount++;
}

uint16_t PulseCounter::readPulses()
{
    uint16_t c = _pulseCount;
    reset();
    return c;
}

uint16_t PulseCounter::peek()
{
    return _pulseCount;
}

void PulseCounter::reset()
{
    _pulseCount = 0;
}

