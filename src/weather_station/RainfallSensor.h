#pragma once

#include "PulseCounter.h"

#define MINUTES_TO_RECORD   (60*24)

class RainfallSensorClass : public PulseCounter {
public:
    RainfallSensorClass(uint8_t pin);
    // note: clears pulses
    void addPulseMinute();
    uint16_t pulsesMinutes(uint16_t minutes=1);
    float rainfallMinutes(uint16_t minutes=1);

protected:
    uint8_t pulseHistory[MINUTES_TO_RECORD];
    uint16_t ptr;
    uint16_t count;

    uint16_t pulsesInRange(uint16_t from, uint16_t to);

};

extern RainfallSensorClass RainfallSensor;

