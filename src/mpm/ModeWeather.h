#pragma once

#include <Mode.h>
#include "WeatherPacket.h"

#define API_KEY         "GED0JXRS9NWB7LYV"
#define URL_TEMPLATE    F("http://api.thingspeak.com/update?api_key={k}&field1={1}&field2={2}&field3={3}&field4={4}&field5={5}&field6={6}&field7={7}&field8={8}")

class ModeWeather_ : public Mode{
public:
    ModeWeather_();
    void begin();

    // Called when this mode is activated
    void modeStart();

    // Called when this mode is de-activated
    void modeStop();

    // Called periodically while mode is active
    void modeUpdate();

    // Called when new weather data comes in from the weather station
    void handleData();

    // Called when we want to check to see if there is a new message from the API
    // This is done OLED_MESSAGE_DELAY_S seconds after weather data is received
    // so as not to have the [blocking] HTTP call interfere with new data coming
    // in from the weather station.
    void updateMessage();

    // Change the OLED display to show the last received weather data
    void displayLastData();

protected:
    uint8_t magicBuf[2];
    uint8_t magicPtr;
    bool inPacket;
    uint8_t dataPtr;
    WeatherUnion packet;
    uint32_t lastRead;
    uint32_t lastSeq;
    uint32_t messageCheckTimer;
    String lastDataReceived;
    uint32_t messageTimeout;
    bool messageGot;

    void resetData();
    bool checkMagic();
    void uploadThingspeak();
};

extern ModeWeather_ ModeWeather;

