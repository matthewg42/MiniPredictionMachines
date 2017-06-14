#include <MutilaDebug.h>
#include "HC12Serial.h"
#include "Config.h"

HC12Serial_ HC12Serial(HC12_RX_PIN, HC12_TX_PIN, HC12_SET_PIN);

HC12Serial_::HC12Serial_(uint8_t rxPin, uint8_t txPin, uint8_t setPin) : 
    SoftwareSerial(rxPin, txPin),
    _setPin(setPin)
{
}

void HC12Serial_::begin(long baud)
{
    DB(F("HC12Serial::begin baud="));
    DBLN(baud);
    pinMode(_setPin, OUTPUT);
    setModeOff();
    SoftwareSerial::begin(baud);
}

void HC12Serial_::setModeOff()
{
    DBLN(F("HC12Serial::setModeOff"));
    _setMode = false;
    digitalWrite(_setPin, HIGH);
}

void HC12Serial_::setModeOn()
{
    DBLN(F("HC12Serial::setModeOn"));
    _setMode = true;
    digitalWrite(_setPin, LOW);
}

void dumpString(const char* prefix, String data) {
    DB(prefix);
    DB(F(": ["));
    for (uint8_t i=0; i<data.length(); i++) {
        DB(data[i], HEX);
        if (i<data.length()-1) { DB(" "); }
    }
    DB("] \"");
    data.replace("\r", "\\r");
    data.replace("\n", "\\n");
    DB(data);
    DBLN('"');
}

bool HC12Serial_::sendATCommand(const char* cmd)
{
    bool prevSetMode = _setMode;
    if (!_setMode) { 
        setModeOn(); 
        delay(50);
    }
    String tx = cmd;
    tx += '\n';
    dumpString("TX", tx);
    print(tx);
    String rx = readStringUntil('\n');
    dumpString("RX", rx);
    if (!prevSetMode) { 
        setModeOff(); 
    }
    return rx.substring(0,2) == "OK";
}

bool HC12Serial_::checkComms()
{
    return sendATCommand("AT");
}

