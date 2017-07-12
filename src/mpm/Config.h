#pragma once

#include <Arduino.h>

// Pins and hardware settings
const uint8_t SW_UP_PIN                 = D0;
const uint8_t SW_DOWN_PIN               = D4;
const uint8_t HC12_SET_PIN              = D1;
const uint8_t HC12_TX_PIN               = D2;
const uint8_t HC12_RX_PIN               = D3;
const uint32_t HC12_BAUD                = 4800;
const uint8_t OLED_SCK_PIN              = D6;
const uint8_t OLED_SDA_PIN              = D5;
const uint8_t HEARTBEAT_PIN             = D8;
const bool HEARTBEAT_INV                = false;

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

// Should not contain trailing / - it will be added when used
#define API_BASE_URL "http://192.168.1.14:8888"

