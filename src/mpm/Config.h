#pragma once

#include <Arduino.h>

#define     SW_UP_PIN               D0
#define     SW_DOWN_PIN             D4
#define     HC12_SET_PIN            D1
#define     HC12_TX_PIN             D2
#define     HC12_RX_PIN             D3
#define     HC12_BAUD               9600
#define     OLED_SCK_PIN            D6
#define     OLED_SDA_PIN            D5
#define     HEARTBEAT_PIN           D8
#define     HEARTBEAT_INV           false

#define     SET_ACCT_UPD            F("Account Updated")
#define     SET_NTP_SERVER          F("Time Server")
#define     NTP_REFRESH_PERIOD_S    1800
#define     NTP_RETRY_PERIOD_S      10

