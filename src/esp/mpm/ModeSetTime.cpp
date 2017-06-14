#include <EspApConfigurator.h>
#include "ModeSetTime.h"
#include "Config.h"

ModeSetTime_ ModeSetTime;

ModeSetTime_::ModeSetTime_() 
{
    // don't go nuts.
    setUpdatePeriod(500);
}

void ModeSetTime_::begin()
{
    DBLN(F("ModeSetTime::begin"));
}

void ModeSetTime_::modeStart()
{
    DBLN(F("ModeSetTime::modeStart"));
}

void ModeSetTime_::modeStop()
{
    DBLN(F("ModeSetTime::modeStop"));
}

void ModeSetTime_::modeUpdate()
{
    DBLN(F("ModeSetTime::modeUpdate"));

    if (!EspApConfigurator.isConnected()) {
        DBLN(F("not connected to network, waiting..."));
        return;
    }

    // TODO: try to do the NTP thing
}

bool ModeSetTime_::isFinished()
{
    // TODO: test is we have a valid time, and if so, say we're done.
}



