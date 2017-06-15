#include <EspApConfigurator.h>
#include "ModeOledTest.h"
#include "Config.h"
#include "OLED.h"

ModeOledTest_ ModeOledTest;

ModeOledTest_::ModeOledTest_() 
{
    // don't go nuts.
    setUpdatePeriod(100);
}

void ModeOledTest_::begin()
{
    DBLN(F("ModeOledTest::begin"));
}

void ModeOledTest_::modeStart()
{
    DBLN(F("ModeOledTest::modeStart"));
    _isDone = false;
    _counter = 0;

    OLED.drawStr(0, 20, "Oh Hai");
    OLED.sendBuffer();
}

void ModeOledTest_::modeStop()
{
    DBLN(F("ModeOledTest::modeStop"));
}

void ModeOledTest_::modeUpdate()
{
    _isDone = _counter > 30;

    _counter++;
}

bool ModeOledTest_::isFinished()
{
    return _isDone;
}


