#include <EEPROM.h>
#include <Mode.h>
#include <MutilaDebug.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <PersistentSettingBool.h>
#include <EspApConfigurator.h>
#include <ModeWifiClient.h>
#include <SoftwareSerial.h>
#include "ModeUpdateAccount.h"
#include "ModeCheckHC12.h"
//#include "ModeUploadData.h"
#include "HC12Serial.h"
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

    HC12Serial.begin();
    delay(200);

    ModeUpdateAccount.begin();
    ModeCheckHC12.begin();
    EspApConfigurator.begin(SW_UP_PIN, HEARTBEAT_PIN, HEARTBEAT_INV);
    switchMode(&ModeUpdateAccount);

    // Enable web server in ModeWifiClient - this just makes testing
    // easier as I don't have to keep connecting to the AP to see
    // how the interface is being rendered...
    //ModeWifiClient.enableHttpServer(true);
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
            switchMode(&ModeCheckHC12);
        } else if (mode == &ModeCheckHC12) {
            DBLN("TODO: test OLED mode");
        }
    }
}

