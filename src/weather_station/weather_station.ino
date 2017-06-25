#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
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

ISR(TIMER1_OVF_vect)
{
    TCNT1 = TIMER_MAX;          // reset counter
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
    // let serial finish
    delay(30);

    // Select sleep mode.  To have a wakeup timer, we have to use the least 
    // of the sleep modes: IDLE
    set_sleep_mode(SLEEP_MODE_IDLE);

    sleep_enable();

    // Disable unused peripherals to save more power
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer2_disable();
    power_twi_disable();  

    // Goodnight Arduino
    sleep_mode();

    // Wake up here. What day it is?
    sleep_disable(); 

    // Re-enable peripherals
    power_all_enable();

    // Let serial start
    delay(30);
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

    // Timer interrupt
    TCCR1A = 0;
    TCNT1  = 0; 
    TCCR1B = 0x05;  // prescaler for 1:1024, giving us a timeout of 4.09 seconds.
    TIMSK1 = 0x01;  // enable timer and overflow interrupt

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
        DB("WS ");
        DB(count++);
        DB(" ");
        DBLN(m);
    }

    if (flgTim) {
        flgTim = false;
        unsigned long m = Millis();
        DB("WS ");
        DB(count++);
        DB(" ");
        DBLN(m);
        DBLN(F("Timer interrupt triggered"));
    }

    goSleep();
    DBLN("E:loop");
}

