# Template Arduino Project

## Pre-requisites

* Install the Arduino IDE 1.6.6 or later
** Windows & Mac users may find a download link here: https://www.arduino.cc/en/Main/Software
** Major Linux distros carry it in their software repositories, or the link above may be used
* In the Arduino IDE, install ESP8266 board support from Tools -> Board -> Boards Manager
* In the Arduino IDE, install ESP8266 tools from Sketch -> Include Library -> Manage Libraries

## Building Using the Arduino IDE

This method is preferred on Windows and for casual users who just want to build and use the project.

* Open Arduino IDE 
* Open firmware/firmware.ino
* Set the board you are using (under the Tools -> Board menu)
* Connect board with USB cable 
* Click the Upload button on the tool bar

## Using make on Linux

This alternative build system may also be used. It is an alternative to using the Arduino IDE and may be preferred by some users. 

* Install the esp/Arduino makefile: https://github.com/plerup/makeEspArduino
* Edit the esp.mk file and set the include line to point at where you installed makeEspArduino.mk (or set the ESP_MAKEFILE environment variable)
* Edit firmware/Makefile and uncomment a BOARD for the board you're using (to see a list of possible boards, run "make list_boards" from the firmware directory)
* Connect your ESP board with a USB cable
* Press and hold the flash button on the board and use the command "make flash" from the firmware directory

