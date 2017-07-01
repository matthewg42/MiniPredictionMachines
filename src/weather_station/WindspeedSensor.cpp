#include <MutilaDebug.h>
#include "WindspeedSensor.h"
#include "Config.h"

PulseCounter WindspeedSensor(WINDSPEED_PIN);

float calculateWindspeedMs(uint16_t pulseCount, uint32_t periodMs)
{
    float hz = (pulseCount*1000.)/periodMs;
    float windspeed = WINDSPEED_MS_PER_HZ*hz;
    return windspeed;
}

