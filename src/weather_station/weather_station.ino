#include <Arduino.h>
#include <avr/sleep.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Includes used by other classes (must put here for Arduino IDE)
#include <OneWire.h>
#include <DallasTemperature.h>

// Include our classes for the various components
#include "HC12Serial.h"
#include "MoistureSensor.h"
#include "TemperatureSensor.h"

// And general configuration like pins
#include "Config.h"

volatile bool flgWs;
unsigned long prev = 0;

void wsInt()
{
    flgWs = true;
}

void sendData()
{
    float temperature = TemperatureSensor.getCelcius();
    bool moisture = MoistureSensor.isMoist();

    DBLN("sendData():");
    DB("  temperature = "); DB(temperature); DBLN('C');
    DB("  moisture    = "); DBLN(moisture);

}

void goSleep()
{
    DBLN("goSleep");
    // let serial finish
    delay(30);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); 
    sleep_mode();  

    // When the device wakes up, it resumes execution here
    sleep_disable(); 
    // let serial start
    delay(30);
}

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));

    MoistureSensor.begin();
    TemperatureSensor.begin();

    pinMode(WINDSPEED_PIN, INPUT_PULLUP);
    attachInterrupt(0, wsInt, RISING);

    DBLN(F("E:setup"));
}

void loop()
{
    DBLN("S:loop");
    if (flgWs) {
        flgWs = false;
        unsigned long m = Millis();
        DB("WS ");
        DB(m);
        DB(' ');
        DBLN(m-prev);
        prev = m;
    }
    goSleep();
    DBLN("E:loop");
}

