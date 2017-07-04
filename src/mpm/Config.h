#pragma once

#include <Arduino.h>

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

const char SET_ACCT_UPD[] PROGMEM       = "Account Updated";
const char SET_NTP_SERVER[] PROGMEM     = "Time Server";
const uint16_t NTP_REFRESH_PERIOD_S     = 1800;
const uint16_t NTP_RETRY_PERIOD_S       = 10;
const uint16_t OLED_MESSAGE_PERIOD_S    = 61;

const uint8_t WEATHER_PACKET_MAGIC[]    = {0x12, 0x13};
const uint16_t PACKET_READ_TIMEOUT_MS   = 200;

