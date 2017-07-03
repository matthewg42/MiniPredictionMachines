#include <EEPROM.h>
#include <Mode.h>
#include <MutilaDebug.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PersistentSettingBool.h>
#include <PersistentSettingString.h>
#include <EspApConfigurator.h>
#include <ModeWifiClient.h>
#include <SoftwareSerial.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <TimeLib.h>

// Physical devices
#include "HC12Serial.h"
#include "OLED.h"
#include "SWDOWN.h"

// Modes
#include "ModeMessage.h"
#include "ModeWeather.h"
#include "ModeRealTime.h"
//#include "ModeUploadData.h"

// Other
#include "EspID.h"
#include "Config.h"

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

    ModeRealTime.begin();
    ModeWeather.begin();
    ModeMessage.begin();
    EspApConfigurator.begin(SW_UP_PIN, HEARTBEAT_PIN, HEARTBEAT_INV);

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
    ModeWeather.update();
    ModeMessage.update();
}

