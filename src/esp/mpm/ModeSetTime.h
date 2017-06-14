#pragma once

#include <Mode.h>

class ModeSetTime_ : public Mode {
public:
    ModeSetTime_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

extern ModeSetTime_ ModeSetTime;

