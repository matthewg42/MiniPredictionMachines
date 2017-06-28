#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>

class HC12SerialClass : public SoftwareSerial {
public:
    HC12SerialClass(uint8_t rxPin, uint8_t txPin, uint8_t setPin);
    void begin(long baud);
    void atCommandMode(bool on);

protected:
    uint8_t _setPin;

};

extern HC12SerialClass HC12Serial;

