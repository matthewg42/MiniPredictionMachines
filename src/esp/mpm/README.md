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


