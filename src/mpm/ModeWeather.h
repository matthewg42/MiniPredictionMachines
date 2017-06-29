#pragma once

#include <Mode.h>

class ModeWeather_ : public Mode{
public:
    ModeWeather_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    void resetBuffer();
    void handleMessage();

protected:
    String message;

};

extern ModeWeather_ ModeWeather;

