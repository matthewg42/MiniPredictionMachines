#pragma once

#include <Arduino.h>
#include <stdint.h>

// Digital sensors
const uint8_t WINDSPEED_PIN             = 2;
const uint8_t RAINFALL_PIN              = 3;
const uint8_t TEMPERATURE_PIN           = 4;
const uint8_t MOISTURE_PIN              = 5;

// RGB leds
const uint8_t LED_WS2811_PIN            = 6;

// HC12
const uint8_t WIRELESS_CS_PIN           = 7;
const uint8_t TX_SOFT_PIN               = 8;
const uint8_t RX_SOFT_PIN               = 9;

// GPS (for future use)
const uint8_t GPS_CS_PIN                = 10;

// Buttons
const uint8_t SW_A_PIN                  = 11;
const uint8_t SW_B_PIN                  = 12;

// Analog/other inputs
const uint8_t VBATT_PIN                 = A0;
const uint8_t VANE_PIN                  = A1;
const uint8_t TX_SOFT2_PIN              = A2;
const uint8_t RX_SOFT2_PIN              = A3;
const uint8_t SDA_PIN                   = A4;
const uint8_t SCLK_PIN                  = A5;

// Comms speed for HC12 device
const uint32_t HC12_BAUD                = 9600;

// Tune this based on measuements from an external device with an 
// accurate clock. It's not going to be perfect because the clock
// in the nano is not temperature stabalized - we will just do our
// best to have a fairly sane timekeeper
const uint16_t WDT_PERIOD_MS            = 500;

// How many seconds between calling sendData()
#ifdef UPDATE_PERIOD
// We do this thing with the UPDATE_PERIOD define, so I can quickly
// change on the command line or in the Makefile for testing.
const uint8_t SEND_DATA_PERIOD_SEC      = UPDATE_PERIOD;
#else
const uint8_t SEND_DATA_PERIOD_SEC      = 60;
#endif

// How many seconds to save a chunk of rain data
const uint8_t RAIN_SAVE_PERIOD_SEC      = 60;
const uint8_t RAINFALL_DEBOUNCE_COUNT   = 2;

// Windspeed calibration. We use a constant to prevent any doubt about
// casting in the formula
const float WINDSPEED_MS_PER_HZ         = 0.7;

// See doc/RainfallCalibration.md for how this was computed
const float RAINFALL_MM_PER_PULSE       = 0.319951;

// Send before the weather packet as an indicator that the thing
// that follows is a weather packet
const uint8_t WEATHER_PACKET_MAGIC[]    = {0x12, 0x13};

// How many samples to take when measuring voltage of battery, 
// resistance of voltage divider in K-Ohms, and reference voltage
const uint8_t VBATT_SAMPLES             = 8;
const uint8_t VBATT_R1                  = 100;
const uint8_t VBATT_R2                  = 100;
const float VBATT_VREF                  = 5.0;


