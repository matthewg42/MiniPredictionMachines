#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Includes used by other classes (must put here for Arduino IDE)
#include <OneWire.h>
#include <DallasTemperature.h>

// Include our classes for the various components
#include "HC12Serial.h"
#include "MoistureSensor.h"
#include "TemperatureSensor.h"

// And general configuration like pins
#include "Config.h"

#define DEBOUNCE_MS     15
#define TIMER_MAX       34286

volatile bool flgWs = false;
volatile bool flgTim = false;
unsigned long count = 0;
volatile unsigned long debounceStart = 0;

ISR(WDT_vect)
{
    flgTim = true;
}

void intHandler()
{
    unsigned long m = Millis();
    if (m - debounceStart > DEBOUNCE_MS) {
        debounceStart = m;
        flgWs = true;
    }
}

void sendData()
{
    float temperature = TemperatureSensor.getCelcius();
    bool moisture = MoistureSensor.isMoist();

    DBLN("sendData():");
    DB("  temperature = "); DB(temperature); DBLN('C');
    DB("  moisture    = "); DBLN(moisture);

}

void goSleep()
{
    DBLN("goSleep");
    delay(10);

    // Select sleep mode.  Here using most power-saving mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();     // ready, set...
    sleep_mode();       // sleep

    // Wake up here. What day it is?
    sleep_disable(); 

    // Re-enable peripherals
    power_all_enable();

    // Let serial start
    delay(10);
}

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));


    MoistureSensor.begin();
    TemperatureSensor.begin();

    pinMode(WINDSPEED_PIN, INPUT_PULLUP);

    noInterrupts(); // disable interrupts while we're setting up handlers
    // Interrupt for windspeed pulses
    attachInterrupt(0, intHandler, RISING);

    // Watchdog timer setup
    MCUSR &= ~(1<<WDRF); // Clear the reset flag
  
    /* In order to change WDE or the prescaler, we need to
     * set WDCE (This will allow updates for 4 clock cycles).
     */
    WDTCSR |= (1<<WDCE) | (1<<WDE);

    // set prescaler (2 seconds)
    WDTCSR = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0); 

    // Enable the WD interrupt (no reset)
    WDTCSR |= _BV(WDIE);

    // enable those interrupts
    interrupts();
    DBLN(F("E:setup"));
}

void loop()
{
    DBLN("S:loop");
    if (flgWs) {
        flgWs = false;
        unsigned long m = Millis();
        DB(F("WS "));
        DB(count++);
        DB(" ");
        DBLN(m);
    }

    if (flgTim) {
        flgTim = false;
        unsigned long m = Millis();
        DB(F("WD "));
        DBLN(m);
    }

    goSleep();
    DBLN("E:loop");
}

