#pragma once

#include "PulseCounter.h"

//! Calculate wind speed in meters per second
float calculateWindspeedMs(uint16_t pulseCount, uint32_t periodMs);

extern PulseCounter WindspeedSensor;

