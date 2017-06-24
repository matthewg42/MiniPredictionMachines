#pragma once

#include <Mode.h>

class ModeUpdateAccount_ : public Mode{
public:
    ModeUpdateAccount_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

extern ModeUpdateAccount_ ModeUpdateAccount;

