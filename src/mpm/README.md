Firmware tasks
==============

* AP mode for setup
* Wifi mode for general use has several ongoing tasks
   - Maintain time with NTP
   - Periodically call message API call and display result on OLED
   - Listen for data from weather station & relay to API call

TODO
====

- Serial protocol to send data from weather station to ESP8266
   - modbus?
       - no - we want to push from weather station, and modbus comms start with the destination device
   - binary format:
       - magic, payload length, payload, payload checksum, magic
           - magic: uint16_t constant
           - length: uint8_t length in bytes
           - payload: array of tuples:
               - uint8_t measurement ID:
                   - 0=datetime start as unix seconds (uint32_t optional) 
                   - 1=datetime end as unix seconds (uint32_t optional) 
                   - 4=temperature C (4 byte float)
                   - 5=moisture indicator (bool)
                   - 6=rainfall (4 byte float)
                   - 7=windspeed (4 byte float)
               - up to 4 bytes of value
           - payload checksum: uint16_t CRC for all payload bytes
           - magic: uint16_t constant as first field
   - use same format and pasring / construction code as fire pong events?
- Get API call example from Dominic
- Define API calls

Hardware Config
===============

HC12 device must be in FU2/4800 BAUD mode.

API Calls
=========

Timestreams Message
-------------------

- URL: ...
- Params:
    - id - unique for this MPM station, derived from MAC
    - hmac - auth token based on other params

Device Update
-------------

- URL: blah blah
- Method: POST
- Params:
    - id - unique for this MPM station, derived from MAC
    - hmac - auto token based on other params
    - temp_C - (float) temperature in celcius
    - moisture - (bool) any detection of rain / drizzle?
    - precip_ml_per_h - (float) precipitation in ml / hour (?)
    - windspeed_ms - (float) wind speed in meters / second (?)
- Responses:
    - 200 - OK, got it, thanks

Building
========

Create a file called Makefile.apikeys in this directory containing the following:

    BUILD_EXTRA_FLAGS += -DTIMESTREAMS_API_PUBKEY='"xxxxxxxxxx"'
    BUILD_EXTRA_FLAGS += -DTIMESTREAMS_API_PRIKEY='"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"'

...with values from your timestreams account. This file will not be added to the gitrepository for security reasons.

If you do not use the Makefile build system, edit Config.h and add the following:

#define TIMESTREAMS_API_PUBKEY "xxxxxxxxxx"
#define TIMESTREAMS_API_PRIKEY "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"

