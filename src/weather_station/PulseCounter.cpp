#include "PulseCounter.h"
#include "Config.h"

PulseCounter::PulseCounter(uint8_t pin, uint8_t pinMode) : 
    _pin(pin),
    _pinMode(pinMode)
{
    reset();
}

void PulseCounter::begin() 
{ 
    pinMode(_pin, INPUT_PULLUP); 
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

void PulseCounter::reset()
{
    _pulseCount = 0;
}

