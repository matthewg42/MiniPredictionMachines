#include <EspApConfigurator.h>
#include <stdio.h>
#include "ModeWeather.h"
#include "ModeRealTime.h"
#include "HC12Serial.h"
#include "Config.h"

ModeWeather_ ModeWeather;

ModeWeather_::ModeWeather_() 
{
}

void ModeWeather_::begin()
{
    DBLN(F("ModeWeather::begin"));
    resetBuffer();
}

void ModeWeather_::modeStart()
{
    DBLN(F("ModeWeather::modeStart"));
}

void ModeWeather_::modeStop()
{
    DBLN(F("ModeWeather::modeStop"));
}

void ModeWeather_::modeUpdate()
{
    while(HC12Serial.available()) {
        int c = HC12Serial.read();
        if (c < 0) {
            resetBuffer();
            break;
        } else if (message.length() > 80 || c == '\n' || c == '\r') {
            handleMessage();
        } else {
            message += (char)c;
        }
    }
}

void ModeWeather_::resetBuffer()
{
    message = "";
}

void ModeWeather_::handleMessage()
{
    // SQ=1799 TE=13.31 MO=1 WS=0.00 RM=0.00 RH=0.00 DC=0.12 CS=0
    uint32_t sequence;
    float temperature, windspeed, rainMinute, rainHour, dutyCycle;
    bool moisture;
    uint16_t checksum;
    DB(F("handleMessage: "));
    DBLN(message);
/*    int i = sscanf(message.c_str(), "SQ=%ld TE=%f MO=%d WS=%f RM=%f RH=%f DC=%f CS=%d", 
                &sequence, &temperature, &moisture, &windspeed, 
                &rainMinute, &rainHour, &dutyCycle, &checksum);
    DB(F("i=")); 
    DB(i);
    DB(F("sequence="));
    DB(sequence);
    DB(F(" temperature="));
    DB(temperature);
    DB(F(" moisture="));
    DB(moisture);
    DB(F(" windspeed="));
    DB(windspeed);
    DB(F(" rainMinute="));
    DB(rainMinute);
    DB(F(" rainHour="));
    DB(rainHour);
    DB(F(" dutyCycle="));
    DB(dutyCycle);
    DB(F("checksum="));
    DBLN(checksum); */
    resetBuffer();
}


