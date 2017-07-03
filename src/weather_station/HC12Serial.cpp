#include <MutilaDebug.h>
#include "HC12Serial.h"
#include "Config.h"

HC12SerialClass HC12Serial(RX_SOFT_PIN, TX_SOFT_PIN, WIRELESS_CS_PIN);

HC12SerialClass::HC12SerialClass(uint8_t rxPin, uint8_t txPin, uint8_t setPin) : 
    SoftwareSerial(rxPin, txPin),
    _setPin(setPin)
{
}

void HC12SerialClass::begin(long baud)
{
    pinMode(_setPin, OUTPUT);
    // by default we want to be in normal comms mode
    atCommandMode(false);
    SoftwareSerial::begin(baud);
}

void HC12SerialClass::atCommandMode(bool on)
{
    // It's inverted logic - pull SET to LOW to activate command mode
    digitalWrite(_setPin, on ? LOW : HIGH);
}

void HC12SerialClass::sleep()
{
    atCommandMode(true);
    DBLN(F("HC12 sleep... "));
    print(F("AT+SLEEP\r"));
    delay(10);
    atCommandMode(false);
    
}

void HC12SerialClass::wakeup()
{
    // HC12 wakes up when taken out of AT mode 
    DBLN(F("HC12 wakeup"));
    atCommandMode(true);
    delay(10);
    atCommandMode(false);
}

