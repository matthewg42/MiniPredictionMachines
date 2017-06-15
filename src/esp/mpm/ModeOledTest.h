#pragma once

#include <Mode.h>

class ModeOledTest_ : public Mode{
public:
    ModeOledTest_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

protected:
    bool _isDone;
    int _counter;

};

extern ModeOledTest_ ModeOledTest;

