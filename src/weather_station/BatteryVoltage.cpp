#include <VIPCalculation.h>
#include <MutilaDebug.h>
#include "BatteryVoltage.h"
#include "Config.h"

BatteryVoltageClass BatteryVoltage(VBATT_PIN);

BatteryVoltageClass::BatteryVoltageClass(uint8_t pin) :
    _pin(pin)
{
}

void BatteryVoltageClass::begin()
{
    // no need to explicitly set input mode for analog pins
}

float BatteryVoltageClass::volts()
{
    // Sample some number of times and divide to get average value
    uint16_t sum = 0;
    for (uint8_t i=0; i<VBATT_SAMPLES; i++) {
        sum += analogRead(_pin);
    }
    return vDivVolts(sum / VBATT_SAMPLES, VBATT_R1, VBATT_R2, VBATT_VREF);
}
