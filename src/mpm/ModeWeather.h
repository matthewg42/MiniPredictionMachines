#pragma once

#include <Mode.h>
#include "WeatherPacket.h"

class ModeWeather_ : public Mode{
public:
    ModeWeather_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    void handleData();

protected:
    uint8_t magicBuf[2];
    uint8_t magicPtr;
    bool inPacket;
    uint8_t dataPtr;
    WeatherUnion packet;
    unsigned long lastRead;
    uint32_t lastSeq;

    void resetData();
    bool checkMagic();
};

extern ModeWeather_ ModeWeather;

