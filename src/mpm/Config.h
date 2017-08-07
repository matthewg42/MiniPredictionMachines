#pragma once

#include <Arduino.h>

// Pins and hardware settings
const uint8_t SW_UP_PIN                 = D0;
const uint8_t SW_DOWN_PIN               = D4;
const uint8_t HC12_SET_PIN              = D1;
const uint8_t HC12_TX_PIN               = D3;
const uint8_t HC12_RX_PIN               = D2;
const uint32_t HC12_BAUD                = 4800;
const uint8_t OLED_SCK_PIN              = D6;
const uint8_t OLED_SDA_PIN              = D5;
const uint8_t HEARTBEAT_PIN             = D8;
const bool HEARTBEAT_INV                = false;

// Access point password
#define AP_PASSPHRASE                   "sunshine"

// Status messages and such
#define SET_NTP_SERVER                  "Time Server"
#define SET_LONGITUDE                   "Longitude"
#define SET_LATITUDE                    "Latitude"

// How often to try to sync time with NTP server
const uint32_t NTP_REFRESH_PERIOD_S     = 1800;

// When NTP fails, how long to wait before re-try
const uint32_t NTP_RETRY_PERIOD_S       = 10;

// How long after receipt of weather data we check for a new message
const uint32_t OLED_MESSAGE_DELAY_S     = 5;

// How many seconds to display a message for
const uint32_t OLED_MESSAGE_BLANK_S     = 90;

// Used to identify start of incoming weather data on HC12
const uint8_t WEATHER_PACKET_MAGIC[]    = {0x12, 0x13};

// How long to wait before discarding partially-received weather data
const uint32_t PACKET_READ_TIMEOUT_MS   = 200;

#define OLED_MESSAGE_FONT               u8g2_font_helvR08_tf
const uint8_t OLED_MESSAGE_FONT_HEIGHT  = 8;
const uint8_t OLED_MESSAGE_FONT_VSEP    = 3;

#ifndef DISPLAY_BATTERY_VOLTAGE
#define DISPLAY_BATTERY_VOLTAGE 1
#endif

//////////////////////
// Thingspeak settings
//////////////////////
// Some of these are wrapped in #ifdefs so they can be over-ridden from the Makefile using a command line -D option
#define THINGSPEAK_URL_TEMPLATE     F("http://api.thingspeak.com/update?api_key={k}&field1={1}&field2={2}&field3={3}&field4={4}&field5={5}&field6={6}&field7={7}&field8={8}")

#ifndef THINGSPEAK_UPLOAD
// Set to 1 to enable THINGSPEAK functionality, 0 to disable
#define THINGSPEAK_UPLOAD 0
#endif

#ifdef THINGSPEAK_API_KEY
// Define your THINGSPEAK write API key here.  Remember, don't commit
// API keys to git, or publish them some other way.
#define THINGSPEAK_API_KEY          F("0000000001111111")
#endif


///////////////////////
// Timestreams settings
// ////////////////////
// Some of these are wrapped in #ifdefs so they can be over-ridden from the Makefile using a command line -D option
#ifndef TIMESTREAMS_UPLOAD
// Set to 1 to enable timestreams functionality, 0 to disable
#define TIMESTREAMS_UPLOAD 1
#endif

// You can define API key details here, but remember, live API keys should
// not be commited to the git repo!  We wrap in an #ifdef in case we're
// building with the Makefile and have used a command-line #define
#ifndef TIMESTREAMS_API_PRIKEY
#define TIMESTREAMS_API_PRIKEY "00000000001111111111222222222233"
#endif

// Note: should NOT contain trailing /
#define API_BASE_URL                F("http://future.thepredictionmachine.org/wp-content/plugins/the-future-machine/api/v1")

// How many parameters we might have in an API call (including hmac)
#define HTTP_PARAMIZER_MAX_PARAMS   15


