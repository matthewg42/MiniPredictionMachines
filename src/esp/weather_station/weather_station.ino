#include <Arduino.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <SoftwareSerial.h>
#include <DebouncedButton.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>

#include "HC12Serial.h"
#include "Config.h"

// See Config.h for pins

DebouncedButton SWA(SW_A_PIN);
DebouncedButton SWB(SW_B_PIN);

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));
    SWA.begin();
    SWB.begin();
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    DBLN(F("E:setup"));
}

void loop()
{
    SWA.update();
    SWB.update();

    if (SWA.tapped()) {
        DBLN("SWA tap");
    }
    if (SWB.tapped()) {
        DBLN("SWB tap");
    }
}

