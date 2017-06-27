#include "WindspeedSensor.h"
#include "Config.h"

PulseCounter WindspeedSensor(WINDSPEED_PIN);

float calculateWindspeedMs(uint16_t pulseCount, uint32_t periodMs)
{
    return WINSPEED_MS_PER_HZ * (pulseCount*1000.0/periodMs);
}

