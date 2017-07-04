#include <EspApConfigurator.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Millis.h>
#include <stdio.h>
#include "ModeMessage.h"
#include "OLED.h"
#include "Config.h"

ModeMessage_ ModeMessage;

ModeMessage_::ModeMessage_() 
{
    setUpdatePeriod(OLED_MESSAGE_PERIOD_S*1000);
}

void ModeMessage_::begin()
{
    DBLN(F("ModeMessage::begin"));
    display("Connecting to Wifi...");
}

void ModeMessage_::modeStart()
{
    DBLN(F("ModeMessage::modeStart"));
}

void ModeMessage_::modeStop()
{
    DBLN(F("ModeMessage::modeStop"));
}

void ModeMessage_::modeUpdate()
{
    HTTPClient http;
    yield();
    http.begin(MESSAGE_URL);
    int httpCode = http.GET();
    if (httpCode > 0) {
        _message = http.getString();
        display(_message);
    } else {
        // clear();
    }
}

u8g2_uint_t getCharWidth(char c)
{
    char buf[2];
    buf[0] = c;
    buf[1] = 0;
    return OLED.getStrWidth(buf);
}

void ModeMessage_::display(String message)
{
    DB(F("ModeMessage::display "));
    DBLN(message);
    OLED.clearBuffer();
    OLED.setFont(MESSAGE_FONT);            // choose a suitable font
    
    const uint8_t maxLines = OLED.getDisplayHeight() / (MESSAGE_FONT_HEIGHT+MESSAGE_FONT_VSEP);
    String lineText[maxLines];
    uint8_t lines = 0;
    int8_t lastSpace = -1;
    for (uint8_t i=0; message[i]!=0; i++) {
        if (message[i] == '\r' || message[i] == '\n' || message[i] == '|') {  
            // explicit line break
            if (lines >= maxLines-1) {
                // if we're out of lines, stop adding more letters
                break;
            } else {
                // continue on next line
                lines++;
                lastSpace = -1;
                continue;
            }
        } else if (OLED.getStrWidth(lineText[lines].c_str()) + getCharWidth(message[i]) >= OLED.getDisplayWidth()) {
            // word wrap
            if (lines >= maxLines-1) {
                // if we're out of lines, stop adding more letters
                break;
            }
            if (lastSpace>=0) {
                // 1. copy last partial word from the end of this line to the next line
                lineText[lines+1] = lineText[lines].substring(lastSpace+1);
                // 2. remove last partial word from end of this line
                lineText[lines].remove(lastSpace);
                lastSpace = -1;
            }
            // 3. text from here goes on next line
            lines++;
        }
        lineText[lines] += message[i];
        if (message[i] == ' ') {
            lastSpace = lineText[lines].length() - 1;
            //DB(F("Current line=\""));
            //DB(lineText[lines]);
            //DB(F("\" lastSpace idx="));
            //DBLN(lastSpace);
        }
    }
    lines++;

    // Work out where to put it
    for (uint8_t i = 0; i<lines; i++) {
        uint8_t ypos = MESSAGE_FONT_HEIGHT + ((MESSAGE_FONT_HEIGHT+MESSAGE_FONT_VSEP)*i);
        //DB(F("ypos="));
        //if (ypos < 10) { DB("0"); }
        //DB(ypos);
        //DB(F(" line="));
        //DBLN(lineText[i]);
        OLED.drawStr(0, ypos, lineText[i].c_str());
    }
    OLED.sendBuffer();                     // transfer internal memory to the display
}

void ModeMessage_::clear()
{
    DBLN(F("ModeMessage::clear"));
    OLED.clearBuffer();
    OLED.sendBuffer();
}



