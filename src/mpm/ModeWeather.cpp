#include <EspApConfigurator.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Millis.h>
#include <stdio.h>
#include "ModeWeather.h"
#include "ModeRealTime.h"
#include "HC12Serial.h"
#include "OLED.h"
#include "Config.h"

// for system_get_free_heap_size()
extern "C" {
    #include "user_interface.h"
}

ModeWeather_ ModeWeather;

ModeWeather_::ModeWeather_() :
    lastSeq(0),
    messageTimer(0),
    messageGot(false)
{
    resetData();
}

void ModeWeather_::begin()
{
    DBLN(F("ModeWeather::begin"));
}

void ModeWeather_::modeStart()
{
    DBLN(F("ModeWeather::modeStart"));
}

void ModeWeather_::modeStop()
{
    DBLN(F("ModeWeather::modeStop"));
}

void ModeWeather_::modeUpdate()
{
    // Timeout
    if ((magicPtr>0 || dataPtr>0) && Millis() - lastRead > PACKET_READ_TIMEOUT_MS) {
        DBLN(F("timeout"));
        resetData();
    }

    while(HC12Serial.available()) {
        int c = HC12Serial.read();
        if (c < 0) {
            DBLN(F("serial error"));
            resetData();
            break;
        }
        lastRead = Millis();
        if (!inPacket) {
            // do the magic...
            magicBuf[magicPtr++] = (uint8_t)c;
            if (!checkMagic()) { 
                DBLN(F("bad magic"));
                resetData(); 
                break; 
            }
            if (magicPtr == 2) {
                inPacket = true;
            }
            break;
        } else {
            packet.bytes[dataPtr++] = (uint8_t)c;
            if (dataPtr >= sizeof(WeatherPacket)) {
                handleData();
                resetData();
            }
        }
    }

    // Decide if we need to update the message
    if (!messageGot && Millis() > messageTimer + (OLED_MESSAGE_DELAY_S*1000)) {
        updateMessage();
    }

    // Blank message if it's been there for ages
    if (messageGot && Millis() > messageTimer + (OLED_MESSAGE_BLANK_S*1000)) {
        DBLN(F("message timeout"));
        messageGot = false;
        OLED.clearBuffer();
        OLED.sendBuffer();
    }
}

void ModeWeather_::updateMessage()
{
    DBLN(F("updateMessage"));
    messageTimer = Millis();

    // This might take a little while, so give the ESP a chance to do it's stuff
    yield();

    HTTPClient http;
    http.begin(API_URL_MESSAGE);
    int httpCode = http.GET();
    if (httpCode == 200) {
        OLED.displayText(http.getString().c_str(), 'C', 'M');
    } else {
        DB(F("failed, code="));
        DBLN(httpCode);
    }
    messageGot = true;
}

void ModeWeather_::handleData()
{
    messageTimer = Millis();
    messageGot = false;

    if (!weatherPacketCsTest(&packet.data)) {
        DBLN(F("bad checksum"));
    } else {
        DBLN(F("good checksum"));
    }

    // Only handle a given message once
    if (packet.data.sequenceNumber != lastSeq) {
        lastSeq = packet.data.sequenceNumber;
        DB(ModeRealTime.isoTimestamp());
        DB(F(" SQ="));
        DB(packet.data.sequenceNumber);
        DB(F(" TE="));
        DB(packet.data.temperatureC);
        DB(F(" MO="));
        DB(packet.data.moisture);
        DB(F(" WS="));
        DB(packet.data.windSpeedMs);
        DB(F(" RM="));
        DB(packet.data.rainFallMmMinute);
        DB(F(" RH="));
        DB(packet.data.rainFallMmHour);
        DB(F(" RD="));
        DB(packet.data.rainFallMmDay);
        DB(F(" BV="));
        DB(packet.data.batteryVoltage);
        DB(F(" DC="));
        DB(packet.data.dutyCycle);
        DB(F(" CS="));
        DBLN(packet.data.checksum);

        uploadThingspeak();
    }
}

void ModeWeather_::resetData()
{
    memset(magicBuf, 0, 2);
    magicPtr = 0;
    inPacket = false;
    dataPtr = 0;
}

bool ModeWeather_::checkMagic()
{
    for (uint8_t i=0; i<magicPtr && i<2; i++) {
        if (magicBuf[i] != WEATHER_PACKET_MAGIC[i]) {
            return false;
        }
    }
    return true;
}

void ModeWeather_::uploadThingspeak()
{
    HTTPClient http;
    
    String url = URL_TEMPLATE;
    url.replace("{k}", API_KEY);
    url.replace("{1}", String(packet.data.temperatureC, 3));
    url.replace("{2}", String(packet.data.moisture));
    url.replace("{3}", String(packet.data.windSpeedMs, 3));
    url.replace("{4}", String(packet.data.rainFallMmMinute, 3));
    url.replace("{5}", String(packet.data.rainFallMmHour, 3));
    url.replace("{6}", String(packet.data.rainFallMmDay, 3));
    url.replace("{7}", String(packet.data.batteryVoltage, 3));
    url.replace("{8}", String(system_get_free_heap_size()));

    yield();

    http.begin(url.c_str());
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        DB(F("Thingspeak response: "));
        DBLN(payload);
    }

}
