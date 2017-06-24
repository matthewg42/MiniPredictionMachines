#pragma once

#include <Mode.h>

class ModeCheckHC12_ : public Mode{
public:
    ModeCheckHC12_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

protected:
    bool _testPassed;

};

extern ModeCheckHC12_ ModeCheckHC12;

