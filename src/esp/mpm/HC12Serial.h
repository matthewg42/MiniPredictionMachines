#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include "Config.h"

class HC12Serial_ : public SoftwareSerial {
public:
    HC12Serial_(uint8_t rxPin, uint8_t txPin, uint8_t setPin);
    void begin(long baud=HC12_BAUD);
    void setModeOn();
    void setModeOff();
    bool sendATCommand(const char* cmd);
    bool checkComms();

protected:
    uint8_t _setPin;
    bool _setMode;

};

extern HC12Serial_ HC12Serial;

