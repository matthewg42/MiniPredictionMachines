#pragma once

#include <U8g2lib.h>
#include "Config.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C OLED;

