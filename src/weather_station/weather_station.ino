#include <Arduino.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <SoftwareSerial.h>
#include <DebouncedButton.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>

// Temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

#include "HC12Serial.h"
#include "Config.h"

DebouncedButton SWA(SW_A_PIN);
DebouncedButton SWB(SW_B_PIN);

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature DS18B20(&oneWire);

float getTemperatureInC()
{
    DB("Reading temperature... ");
    DS18B20.requestTemperatures();
    float c = DS18B20.getTempCByIndex(0);
    DB(c);
    DBLN('C');
    return c;
}

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));
    SWA.begin();
    SWB.begin();
    DS18B20.begin();
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    DBLN(F("E:setup"));
}

void loop()
{
    SWA.update();
    SWB.update();

    if (SWA.tapped()) {
        getTemperatureInC();
    }
    if (SWB.tapped()) {
        DBLN("SWB tap");
    }
}

