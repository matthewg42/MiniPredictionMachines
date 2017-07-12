#pragma once

#include <MutilaDebug.h>
#include "OLED.h"
#include "Config.h"

OLEDClass OLED(U8G2_R0, OLED_SCK_PIN, OLED_SDA_PIN, D0);

OLEDClass::OLEDClass(const u8g2_cb_t *rotation, uint8_t clock, uint8_t data, uint8_t reset) :
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C(rotation, clock, data, reset)
{
}

u8g2_uint_t OLEDClass::getCharWidth(char c)
{
    char buf[2];
    buf[0] = c;
    buf[1] = 0;
    return OLED.getStrWidth(buf);
}

u8g2_uint_t OLEDClass::drawStrR(u8g2_uint_t x, u8g2_uint_t y, const char *s)
{
    return drawStr(x-getStrWidth(s), y, s);
}

void OLEDClass::displayText(const char* text, char hAlign, char vAlign)
{
    DB(F("ModeMessage::display "));
    DBLN(text);
    clearBuffer();
    setFont(OLED_MESSAGE_FONT);            // choose a suitable font
    
    const uint8_t maxLines = getDisplayHeight() / (OLED_MESSAGE_FONT_HEIGHT+OLED_MESSAGE_FONT_VSEP);
    String lineText[maxLines];
    uint8_t lines = 0;
    int8_t lastSpace = -1;
    for (uint8_t i=0; text[i]!=0; i++) {
        if (text[i] == '\r' || text[i] == '\n' || text[i] == '|') {  
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
        } else if (getStrWidth(lineText[lines].c_str()) + getCharWidth(text[i]) >= getDisplayWidth()) {
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
        lineText[lines] += text[i];
        if (text[i] == ' ') {
            lastSpace = lineText[lines].length() - 1;
        }
    }
    lines++;

    uint8_t blockHeight = (OLED_MESSAGE_FONT_HEIGHT+OLED_MESSAGE_FONT_VSEP)*lines;
    uint8_t vOffset = 0;
    switch (vAlign) {
    case 'M':
        vOffset = (getDisplayHeight() - blockHeight) / 2;
        break;
    case 'B':
        vOffset = getDisplayHeight() - blockHeight;
        break;
    }

    // Work out where to put it
    for (uint8_t i=0; i<lines; i++) {
        uint8_t ypos = vOffset + OLED_MESSAGE_FONT_HEIGHT + ((OLED_MESSAGE_FONT_HEIGHT+OLED_MESSAGE_FONT_VSEP)*i);
        uint8_t xpos = 0;
        switch (hAlign) {
        case 'C':
            xpos = (getDisplayWidth() - getStrWidth(lineText[i].c_str())) / 2;
            break;
        case 'R':
            xpos = getDisplayWidth() - getStrWidth(lineText[i].c_str());
            break;
        }
        drawStr(xpos, ypos, lineText[i].c_str());
    }
    sendBuffer(); 
}


