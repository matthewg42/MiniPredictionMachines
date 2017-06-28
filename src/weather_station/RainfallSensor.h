#pragma once

#include "PulseCounter.h"

#define MINUTES_TO_RECORD   60

class RainfallSensorClass : public PulseCounter {
public:
    RainfallSensorClass(uint8_t pin);
    // note: clears pulses
    void addPulseMinute();
    float rainfallLastMinute();
    float rainfallLastHour();

protected:
    uint8_t pulseHistory[MINUTES_TO_RECORD];
    uint8_t ptr;
    uint8_t count;

};

extern RainfallSensorClass RainfallSensor;

