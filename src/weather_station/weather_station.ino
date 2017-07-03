#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <VIPCalculation.h>
#include <SoftwareSerial.h>
#include <Millis.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Includes used by other classes (must put here for Arduino IDE)
#include <OneWire.h>
#include <DS18B20.h>

// Include our classes for the various components
#include "HC12Serial.h"
#include "MoistureSensor.h"
#include "TemperatureSensor.h"
#include "WindspeedSensor.h"
#include "RainfallSensor.h"
#include "BatteryVoltage.h"

// And general configuration like pins
#include "WeatherPacket.h"
#include "Config.h"

// Flags which will set from interrupt handlers (these need the volatile keyword)
volatile bool flgWindspeed = false;
volatile bool flgRainfall = false;
volatile bool flgTimer = false;
uint8_t rainfallDebounceCounter = 0;

// Other globals
uint32_t wakeupCounter = 0;
uint32_t lastSend = 0;
uint32_t lastRainMinute = 0;
uint32_t sendSeqNo = 0;

// Interrupt handlers
ISR(WDT_vect)
{
    flgTimer = true;
}

void rainfallIntHandler()
{
    flgRainfall = true;
}

void windspeedIntHandler()
{
    flgWindspeed = true;
}

// Regular functions
void sendData(uint32_t realMillis)
{
    sendSeqNo++;
    DBLN(F("sending data..."));
    WeatherPacket data;
    data.sequenceNumber = sendSeqNo;
    data.temperatureC = TemperatureSensor.getCelcius();
    data.moisture = MoistureSensor.isMoist();
    data.windSpeedMs = calculateWindspeedMs(WindspeedSensor.readPulses(), realMillis - lastSend);
    data.rainFallMmMinute = RainfallSensor.rainfallMinutes(1);
    data.rainFallMmHour = RainfallSensor.rainfallMinutes(60);
    data.rainFallMmDay = RainfallSensor.rainfallMinutes(60*24);
    data.batteryVoltage = BatteryVoltage.volts();
    data.dutyCycle = (float)millis()/realMillis;
    weatherPacketCsUpdate(&data);

    WeatherUnion wu;
    wu.data = data;

    DB(F("packet size="));
    DB(sizeof(WeatherPacket));
    DB(F(" SQ="));
    DB(data.sequenceNumber);
    DB(F(" TE="));
    DB(data.temperatureC);
    DB(F(" MO="));
    DB(data.moisture);
    DB(F(" WS="));
    DB(data.windSpeedMs);
    DB(F(" RM="));
    DB(data.rainFallMmMinute);
    DB(F(" RH="));
    DB(data.rainFallMmHour);
    DB(F(" RD="));
    DB(data.rainFallMmDay);
    DB(F(" BV="));
    DB(data.batteryVoltage);
    DB(F(" DC="));
    DB(data.dutyCycle);
    DB(F(" CS="));
    DBLN(data.checksum);

    for (uint8_t i=0; i<3; i++) {
        HC12Serial.write(WEATHER_PACKET_MAGIC[0]);
        HC12Serial.write(WEATHER_PACKET_MAGIC[1]);
        for (uint8_t j=0; j<sizeof(WeatherPacket); j++) {
            HC12Serial.write(wu.bytes[j]);
        }
    }
    delay(300);
    HC12Serial.sleep();
}

void goSleep()
{
#ifdef DEBUG
    // this to allow clean serial messages
    delay(10); 
#endif

    // Select sleep mode.  Here using most power-saving mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();     // ready, set...
    sleep_mode();       // sleep

    // Wake up here. What day it is?
    sleep_disable(); 

#ifdef DEBUG
    // this to allow clean serial messages
    delay(10);
#endif
}

void setup()
{
    Serial.begin(115200);
    DBLN(F("\n\nS:setup"));

    HC12Serial.begin(HC12_BAUD);

    // We don't need the HC12 doing anything yet - we'll wake it up before
    // sending data
    HC12Serial.sleep();

    MoistureSensor.begin();
    TemperatureSensor.begin();
    WindspeedSensor.begin();
    RainfallSensor.begin();
    BatteryVoltage.begin();

    noInterrupts(); // disable interrupts while we're setting up handlers

    // Interrupts for pulses which come in from windspeed and rainfall sensors
    attachInterrupt(digitalPinToInterrupt(WINDSPEED_PIN), windspeedIntHandler, FALLING);
    attachInterrupt(digitalPinToInterrupt(RAINFALL_PIN), rainfallIntHandler, FALLING);

    // Watchdog timer setup
    MCUSR &= ~(1<<WDRF); // Clear the reset flag
  
    /* In order to change WDE or the prescaler, we need to
     * set WDCE (This will allow updates for 4 clock cycles).
     */
    WDTCSR |= (1<<WDCE) | (1<<WDE);

    // set prescaler (0.5 second)
    WDTCSR = (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0); 

    // Enable the WD interrupt (no reset)
    WDTCSR |= _BV(WDIE);

    // enable those interrupts
    interrupts();
    DBLN(F("E:setup"));
}

void loop()
{
    if (flgWindspeed) {
        DBLN(F("wind pulse"));
        flgWindspeed = false;
        WindspeedSensor.addPulse();
    }

    if (flgRainfall) {
        flgRainfall = false;
        if (millis() < 100) {
            DBLN(F("Discard spurious rain pulse on reset"));
        } else {
            if (rainfallDebounceCounter == 0) {
                DBLN(F("rain pulse"));
                RainfallSensor.addPulse();
                rainfallDebounceCounter = RAINFALL_DEBOUNCE_COUNT;
            } else {
                DBLN(F("rain pulse (discard bounce)"));
            }
        }
    }

    if (flgTimer) {
        flgTimer = false;
        wakeupCounter++;
        DB(F("wakeup #"));
        DBLN(wakeupCounter);

        uint32_t realMillis = wakeupCounter*WDT_PERIOD_MS;

        // decremement the debounce counter
        if (rainfallDebounceCounter > 0) {
            rainfallDebounceCounter--;
        }

        if (realMillis >= lastRainMinute + ((uint32_t)RAIN_SAVE_PERIOD_SEC*1000)) {
            lastRainMinute = realMillis;
            RainfallSensor.addPulseMinute();
        }

        // One second (two wakeups) before the send, request the temperature be ready by the sensor
        uint32_t tempTime = ((uint32_t)(SEND_DATA_PERIOD_SEC-1)*1000);
        if (realMillis >= lastSend + tempTime && realMillis < lastSend + tempTime + WDT_PERIOD_MS) {
            DBLN(F("requesting temperature read"));
            TemperatureSensor.request();
        }

        // Half a second (one wakeup) before the send, wake up the HC12
        if (realMillis >= lastSend + tempTime + WDT_PERIOD_MS && realMillis < lastSend + tempTime + (2*WDT_PERIOD_MS)) {
            HC12Serial.wakeup();
        }

        if (realMillis >= lastSend + ((uint32_t)SEND_DATA_PERIOD_SEC*1000)) {
            sendData(realMillis);
            lastSend = realMillis;
        }
    }

    goSleep();
}

