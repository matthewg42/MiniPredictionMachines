#include <MutilaDebug.h>
#include "TemperatureSensor.h"
#include "Config.h"

TemperatureSensorClass TemperatureSensor(TEMPERATURE_PIN);

TemperatureSensorClass::TemperatureSensorClass(uint8_t pin) :
    oneWire(pin),
    sensor(&oneWire)
{
    memset(address, 0, 8);
}

void dumpAddress(uint8_t* address) {
    for(uint8_t i=0; i<8; i++) {
        if (address[i] < 0x10) { DB('0'); }
        DB(address[i], HEX);
        if (i<7) { DB(':'); }
    }
}

void TemperatureSensorClass::begin()
{
    sensor.begin();
    if (findSensor()) {
        DB(F("Found DS18B20 @ "));
        dumpAddress(address);
        DBLN();
    } else {
        DBLN(F("WARNING: failed to find DS18B20 device"));
    }
}

void TemperatureSensorClass::request()
{
    sensor.request(address);
}

bool TemperatureSensorClass::ready()
{
    return sensor.available();
}

float TemperatureSensorClass::getCelcius()
{
    return sensor.readTemperature(address);
}

bool TemperatureSensorClass::findSensor()
{
    // Look for a sensor of the right type, and set the address if found...
    oneWire.reset_search();
    while(oneWire.search(address)) {
        // test the type of sensor is right: from DallasTemperature library
        // presumably there are actually more things to check, but I don't
        // know what they are.  Better than nothing - although we expect
        // only one device on this pin anyway, so it's not a big deal.
        if (address[0] == 0x28) {
            return true;
        }
    }

    // Nope, we didn't find the right type of device
    memset(address, 0, 8);
    return true;
}

