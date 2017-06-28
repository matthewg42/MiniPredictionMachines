#include <MutilaDebug.h>
#include "RainfallSensor.h"
#include "Config.h"

RainfallSensorClass RainfallSensor(RAINFALL_PIN);

RainfallSensorClass::RainfallSensorClass(uint8_t pin) :
    PulseCounter(pin),
    ptr(0),
    count(0)
{
    memset(pulseHistory, 0, sizeof(uint8_t) * MINUTES_TO_RECORD);
}

void RainfallSensorClass::addPulseMinute()
{
    Serial.println(F("RainfallSensorClass::addPulseMinute"));
    pulseHistory[ptr] = readPulses();
    ptr = (ptr + 1) % MINUTES_TO_RECORD;
    if (count < MINUTES_TO_RECORD) count++;
}

float RainfallSensorClass::rainfallLastMinute()
{
    // In the first minute of operation, return how many pulses so far...
    if (count == 0) { return peek()*RAINFALL_MM_PER_PULSE; }

    // case 1: we have some number of values in the buffer
    // fetch the value at ptr-1 (wrapping if ptr==0)
    return pulseHistory[ptr>0 ? ptr-1 : MINUTES_TO_RECORD-1] * RAINFALL_MM_PER_PULSE;
}

float RainfallSensorClass::rainfallLastHour()
{
    // Case 1: add up all the rainfall for known minutes
    uint16_t totalPulses = 0;
    for (uint8_t i=0; i<count; i++) {
        totalPulses += pulseHistory[i];
    }

    // Calculate and return
    return RAINFALL_MM_PER_PULSE * totalPulses;
}



