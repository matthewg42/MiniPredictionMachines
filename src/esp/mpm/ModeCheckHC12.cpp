#include <EspApConfigurator.h>
#include "ModeCheckHC12.h"
#include "ModeRealTime.h"
#include "HC12Serial.h"
#include "Config.h"

ModeCheckHC12_ ModeCheckHC12;

ModeCheckHC12_::ModeCheckHC12_() 
{
    // don't go nuts.
    setUpdatePeriod(1000);
}

void ModeCheckHC12_::begin()
{
    DBLN(F("ModeCheckHC12::begin"));
}

void ModeCheckHC12_::modeStart()
{
    DBLN(F("ModeCheckHC12::modeStart"));
    _testPassed = false;
}

void ModeCheckHC12_::modeStop()
{
    DBLN(F("ModeCheckHC12::modeStop"));
}

void ModeCheckHC12_::modeUpdate()
{
    DBLN(F("ModeCheckHC12::modeUpdate"));
    _testPassed = HC12Serial.checkComms();

    DB(F("unix time is: "));
    DBLN(ModeRealTime.unixTime());
}

bool ModeCheckHC12_::isFinished()
{
    return _testPassed;
}


