#include <EspApConfigurator.h>
#include "ModeUpdateAccount.h"
#include "Config.h"

ModeUpdateAccount_ ModeUpdateAccount;

ModeUpdateAccount_::ModeUpdateAccount_() 
{
    // don't go nuts.
    setUpdatePeriod(500);
}

void ModeUpdateAccount_::begin()
{
    DBLN(F("ModeUpdateAccount::begin"));
}

void ModeUpdateAccount_::modeStart()
{
    DBLN(F("ModeUpdateAccount::modeStart"));
}

void ModeUpdateAccount_::modeStop()
{
    DBLN(F("ModeUpdateAccount::modeStop"));
}

void ModeUpdateAccount_::modeUpdate()
{
    DBLN(F("ModeUpdateAccount::modeUpdate"));
    if (EspApConfigurator[SET_ACCT_UPD]->get()!="0") return;

    if (!EspApConfigurator.isConnected()) {
        DBLN(F("not connected to network, waiting..."));
        return;
    }

    // TODO: make API call to set ID
    // On success, set setting SET_ACCT_UPD to true
    // for now, a little randomness
    if (random(40) == 0) {
        DBLN(F("Update success!"));
        EspApConfigurator[SET_ACCT_UPD]->set("1");
        EspApConfigurator[SET_ACCT_UPD]->save();
    } else {
        DBLN(F("update failed, will try again"));
    }
}

bool ModeUpdateAccount_::isFinished()
{
    return EspApConfigurator[SET_ACCT_UPD]->get()!="0";
}



