- MPM firmware:
    - Change AP name to MiniPredictionMachine-<espid>
    - Change AP password to "sunshine"
    - convert /upload call to POST
- Weather Station firmware:
    - Rain daily fading too quick bug - test and fix this!
    - Add power control for moisture sensor using GPS power control line
    - Blinky LED when xmitting data (regular LED on WS8266 pin for now)
    - Voltage in should be <= 5V only!
- Test with final PCBs (waiting for delivery boards from China)
  - in progress - looking good!
- Measure bandwidth usage & do usage calculations
- Set all HC12 units to have the correct baud rate and mode (FU2?)
    - Commands to set up HC12 units:
      AT+FU2
      AT+C042
    - expected results of setup query AT+RX:
      OK+B4800
      OK+RC042
      OK+RP:+20dBm
      OK+FU2
