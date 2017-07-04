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
const char SET_ACCT_UPD[] PROGMEM       = "Account Updated";
const char SET_NTP_SERVER[] PROGMEM     = "Time Server";

// How often to try to sync time with NTP server
const uint16_t NTP_REFRESH_PERIOD_S     = 1800;

// When NTP fails, how long to wait before re-try
const uint16_t NTP_RETRY_PERIOD_S       = 10;

// How long after receipt of weather data we check for a new message
const uint16_t OLED_MESSAGE_DELAY_S     = 8;

// How many seconds to display a message for
const uint16_t OLED_MESSAGE_BLANK_S     = 300;

// Used to identify start of incoming weather data on HC12
const uint8_t WEATHER_PACKET_MAGIC[]    = {0x12, 0x13};

// How long to wait before discarding partially-received weather data
const uint16_t PACKET_READ_TIMEOUT_MS   = 200;

