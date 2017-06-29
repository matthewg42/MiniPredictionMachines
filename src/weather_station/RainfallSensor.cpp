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
    DBLN(F("RainfallSensorClass::addPulseMinute"));
    pulseHistory[ptr] = readPulses();
    ptr = (ptr + 1) % MINUTES_TO_RECORD;
    if (count < MINUTES_TO_RECORD) count++;
}

uint16_t RainfallSensorClass::pulsesMinutes(uint16_t minutes)
{
    DB(F("pulsesMinutes ptr="));
    DB(ptr);
    DB(F(" count="));
    DB(count);
    DB(F(" mins="));
    DB(minutes);
    DB(F(" case: "));
    if (minutes <= ptr) {
        DBLN(1);
        return pulsesInRange(ptr-minutes, ptr-1);
    } else if (ptr == 0) {
        DBLN(2);
        return pulsesInRange(MINUTES_TO_RECORD-minutes, MINUTES_TO_RECORD-1);
    } else {
        DBLN(3);
        return pulsesInRange(0, ptr-1) + pulsesInRange(MINUTES_TO_RECORD-minutes+ptr, MINUTES_TO_RECORD-1);
    }
}

float RainfallSensorClass::rainfallMinutes(uint16_t minutes)
{
    return pulsesMinutes(minutes)*RAINFALL_MM_PER_PULSE; 
}

uint16_t RainfallSensorClass::pulsesInRange(uint16_t from, uint16_t to) 
{
    DB(F("pulsesInRange from="));
    DB(from);
    DB(F(" to="));
    DBLN(to);
    uint16_t pulses = 0;
    for(uint16_t i=from; i<=to && i<MINUTES_TO_RECORD && i<count; i++) {
        pulses += pulseHistory[i];
    }
    return pulses;
}



