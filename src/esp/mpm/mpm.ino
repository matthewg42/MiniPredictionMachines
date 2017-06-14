#include <EEPROM.h>
#include <Mode.h>
#include <MutilaDebug.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <PersistentSettingBool.h>
#include <EspApConfigurator.h>
#include <ModeWifiClient.h>
#include "ModeUpdateAccount.h"
#include "ModeSetTime.h"
//#include "ModeUploadData.h"
#include "Config.h"

Mode* mode = NULL;

void switchMode(Mode* newMode)
{
    if (newMode == mode) { return; }
    if (mode) { mode->stop(); }
    mode = newMode;
    if (newMode) { mode->start(); }
}

void setup() 
{
    Serial.begin(115200);
    delay(50);
    DBLN(F("\n\nS:setup"));

    ModeUpdateAccount.begin();
    ModeSetTime.begin();
//    ModeUploadData.begin();
    EspApConfigurator.begin();

    switchMode(&ModeUpdateAccount);

    // Enable web server in ModeWifiClient - this just makes testing
    // easier as I don't have to keep connecting to the AP to see
    // how the interface is being rendered...
    ModeWifiClient.enableHttpServer(true);
    EspApConfigurator.addSetting(SET_ACCT_UPD, new PersistentSettingBool(EspApConfigurator.nextFreeAddress(), false));

    DBLN(F("E:setup"));
}

void loop() 
{
    // Give timeslice to components
    EspApConfigurator.update();
    mode->update();
    if (mode->isFinished()) {
        if (mode == &ModeUpdateAccount) {
            DBLN(F("Account has been updated, setting time"));
            switchMode(&ModeSetTime);
        } else if (mode == &ModeSetTime) {
            DBLN(F("Time set, uploading"));
            // switchMode(&ModeUploadData);
        }
    }
    delay(100);
}

