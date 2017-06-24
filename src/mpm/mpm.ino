#include <EEPROM.h>
#include <Mode.h>
#include <MutilaDebug.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <PersistentSettingBool.h>
#include <PersistentSettingString.h>
#include <EspApConfigurator.h>
#include <ModeWifiClient.h>
#include <SoftwareSerial.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// Physical devices
#include "HC12Serial.h"
#include "OLED.h"
#include "SWDOWN.h"

// Modes
#include "ModeUpdateAccount.h"
#include "ModeCheckHC12.h"
#include "ModeRealTime.h"
//#include "ModeUploadData.h"

// Other
#include "EspID.h"
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
    DBBEGIN;
    delay(50);
    DBLN(F("\n\nS:setup"));
    
    // Set ID based on mac address
    EspID.begin();
    DB(F("Device ID="));
    DBLN(EspID.get());

    // Initialize OLED and choose a font
    OLED.begin();
    OLED.clearBuffer();
    OLED.setFont(u8g2_font_unifont_t_latin);

    HC12Serial.begin();
    delay(100);

    SWDOWN.begin();

    ModeUpdateAccount.begin();
    ModeCheckHC12.begin();
    ModeRealTime.begin();
    EspApConfigurator.begin(SW_UP_PIN, HEARTBEAT_PIN, HEARTBEAT_INV);
    switchMode(&ModeUpdateAccount);

    // Enable web server in ModeWifiClient - this just makes testing
    // easier as I don't have to keep connecting to the AP to see
    // how the interface is being rendered...
    //ModeWifiClient.enableHttpServer(true);
    EspApConfigurator.addSetting(SET_ACCT_UPD,   new PersistentSettingBool(EspApConfigurator.nextFreeAddress(), false));
    EspApConfigurator.addSetting(SET_NTP_SERVER, new PersistentSettingString(EspApConfigurator.nextFreeAddress(), 64, "time.google.com"));

    DBLN(F("E:setup"));
}

void loop() 
{
    // Give timeslice to components
    EspApConfigurator.update();
    ModeRealTime.update();
    mode->update();
    SWDOWN.update();

    // Debug button presses
    if (SWDOWN.tapped()) { DBLN(F("DOWN Button pressed")); }

    // Mode changes by them finishing
    if (mode->isFinished()) {
        if (mode == &ModeUpdateAccount) {
            switchMode(&ModeCheckHC12);
        } else if (mode == &ModeCheckHC12) {
            // TODO: switch to upload mode
        }
    }
}

