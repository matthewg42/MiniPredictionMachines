#pragma once

#include <Mode.h>
#include "WeatherPacket.h"


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
    void checkWeatherPacket();

    // If we have the time by NTP, then display data on the OLED and upload using the API 
    void handleWeatherData();

    // Called when we want to check to see if there is a new message from the API
    // This is done OLED_MESSAGE_DELAY_S seconds after weather data is received
    // so as not to have the [blocking] HTTP call interfere with new data coming
    // in from the weather station.
    void updateMessage();

    // Change the OLED display to show the last received weather data
    void displayLastData();

    // Display the message if it hasn't timed out
    void displayMessage();

protected:
    uint8_t magicBuf[2];
    uint8_t magicPtr;
    bool inPacket;
    uint8_t dataPtr;
    WeatherUnion packet;
    uint32_t lastRead;
    uint32_t lastSeq;
    uint32_t messageCheckTimer;
    String lastMessage;
    String lastDataReceived;
    uint32_t messageTimeout;
    bool messageGot;
    bool forceDataView;

    void resetData();
    bool checkMagic();
    void uploadThingspeak();
    void uploadTimestreams();
};

extern ModeWeather_ ModeWeather;

