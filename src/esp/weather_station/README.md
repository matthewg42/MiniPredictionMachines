Weather Station 
===============

Devices attached
----------------

* HC12 wireless serial
* DS18B20 one-wire temperature sensor
* Moisture sensor - pin goes high when it is raining / drizzling
* Rainfall sensor - rate of pulses indicates amount of rainfall (over some threshhold)
* Anemometer - rate of pulses relates to windspeed


Tasks
-----

* Read data from sensors
* Periocically send data over HC12 to any listening devices

Complications
-------------

The weather station is powered by a solar battery pack so the firmware must do everything possible to conserve power. This basically boils down to going into sleep mode whenever possible, and waking up using interrupts when it is necessary to update any data value, i.e.

* When a pulse comes in from the anemometer
* When a pulse comes in from the rainfall sensor
* A timer set for periodic actions (once per minute), actions:
   * Read moisture sensor
   * Read temperature
   * Send data for last period using HC12 serial device

After each of these activities the nano should go into the deepest sleep mode it can.

Future expansion
----------------

The board has connectors for extra devices:
* SWA & SWB buttons
* Wind vane for wind direction (analog value)
* GPS (second software serial TX&RX, GPS_CS pin
