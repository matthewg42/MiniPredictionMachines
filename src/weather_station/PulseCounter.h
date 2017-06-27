#pragma once

#include <Arduino.h>
#include <stdint.h>

class PulseCounter {
public:
    //! Constructor
    PulseCounter(uint8_t pin);

    //! Initialize pin
    void begin(uint8_t pinModeSetting=INPUT_PULLUP);

    //! Increment the counter
    void addPulse();

    //! Read pulse counter (and zero it)
    uint16_t readPulses();
    uint16_t peek();

private:
    uint8_t _pin;
    uint16_t _pulseCount;

    void reset();

};


