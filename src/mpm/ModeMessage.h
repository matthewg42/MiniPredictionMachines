#pragma once

#include <Mode.h>
#include "WeatherPacket.h"

#define MESSAGE_URL F("http://192.168.1.14:8888/api/message")
#define MESSAGE_FONT u8g2_font_helvR08_tf
#define MESSAGE_FONT_HEIGHT 8
#define MESSAGE_FONT_VSEP   3

class ModeMessage_ : public Mode{
public:
    ModeMessage_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    void display(String message);
    void clear();

protected:
    String _message;

};

extern ModeMessage_ ModeMessage;

