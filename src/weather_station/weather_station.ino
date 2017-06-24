#include <Arduino.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <SoftwareSerial.h>
#include <DebouncedButton.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>

// Includes used by other classes (must put here for Arduino IDE)
#include <OneWire.h>
#include <DallasTemperature.h>

// Include our classes for the various components
#include "HC12Serial.h"
#include "MoistureSensor.h"
#include "TemperatureSensor.h"

// And general configuration like pins
#include "Config.h"

DebouncedButton SWA(SW_A_PIN);
DebouncedButton SWB(SW_B_PIN);

void sendData()
{
    float temperature = TemperatureSensor.getCelcius();
    bool moisture = MoistureSensor.isMoist();

    DBLN("sendData():");
    DB("  temperature = "); DB(temperature); DBLN('C');
    DB("  moisture    = "); DBLN(moisture);

}

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));

    // Init our classes for various sensors...
    SWA.begin();
    SWB.begin();
    MoistureSensor.begin();
    TemperatureSensor.begin();

    DBLN(F("E:setup"));
}

void loop()
{
    SWA.update();
    SWB.update();

    if (SWA.tapped()) {
        sendData();
    }
    if (SWB.tapped()) {
        DBLN("SWB tap");
    }
}

