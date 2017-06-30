#include <EspApConfigurator.h>
#include <Millis.h>
#include <stdio.h>
#include "ModeWeather.h"
#include "ModeRealTime.h"
#include "HC12Serial.h"
#include "Config.h"

ModeWeather_ ModeWeather;

ModeWeather_::ModeWeather_() :
    lastSeq(0)
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
}

void ModeWeather_::handleData()
{
    if (!weatherPacketCsTest(&packet.data)) {
        DBLN(F("bad checksum"));
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
        DB(F(" CS="));
        DBLN(packet.data.checksum);
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

