#pragma once

#include <Arduino.h>

// Digital sensors
#define WINDSPEED_PIN           2
#define RAINFALL_PIN            3
#define TEMPERATURE_PIN         4
#define MOISTURE_PIN            5

// RGB leds
#define LED_WS2811_PIN          6

// HC12
#define WIRELESS_CS_PIN         7
#define TX_SOFT_PIN             8
#define RX_SOFT_PIN             9

// GPS (for future use)
#define GPS_CS_PIN              10

// Buttons
#define SW_A_PIN                11
#define SW_B_PIN                12

// Analog/other inputs
#define VBATT_PIN               A0
#define VANE_PIN                A1
#define TX_SOFT2_PIN            A2
#define RX_SOFT2_PIN            A3
#define SDA_PIN                 A4
#define SCLK_PIN                A5

// Tune this based on measuements from an external device with an 
// accurate clock. It's not going to be perfect because the clock
// in the nano is no temperature stabalized - we will just do our
// best to have a fairly sane timekeeper
#define WDT_PERIOD_MS           500

// How many seconds between calling sendData()
#define SEND_DATA_PERIOD_SEC    5

#define RAINFALL_DEBOUNCE_COUNT 2

