#include <MutilaDebug.h>
#include <Millis.h>
#include <EspApConfigurator.h>
//#include <TimeLib.h>
#include "ModeRealTime.h"
#include "Config.h"

/*
 * NTP code taken from the TimeNTP_ESP8266WiFi example in TimeLib version 1.5
 * by Michael Margolis & Paul Stoffregen
 * http://playground.arduino.cc/code/time
 *
 */

ModeRealTime_ ModeRealTime;

ModeRealTime_::ModeRealTime_() :
    _lastNtpAttempt(0),
    _lastNtpSuccess(0),
    _unixTime(0),
    _state(ModeRealTime_::Wait)
{
    setUpdatePeriod(1000);
    clearBuf();
}

void ModeRealTime_::begin()
{
    DBLN(F("ModeRealTime::begin"));
    _udp.begin(LOCAL_NTP_PORT);
}

void ModeRealTime_::modeStart()
{
    DBLN(F("ModeRealTime::modeStart"));
    clearBuf();
}

void ModeRealTime_::modeStop()
{
    DBLN(F("ModeRealTime::modeStop"));
}

void ModeRealTime_::modeUpdate()
{
    // If we managed to set time using NTP in the last NTP_REFRESH_PERIOD_S seconds
    // we don't need to do anything - just return
    if (Millis() < _lastNtpSuccess + (NTP_REFRESH_PERIOD_S*1000) && _lastNtpSuccess != 0) {
        return;
    }

    if (Millis() >= _lastNtpAttempt + (NTP_RETRY_PERIOD_S*1000) || _lastNtpAttempt == 0) {
        ntpUpdate();
    }
}

void ModeRealTime_::ntpUpdate()
{
    DBLN("ModeRealTime::ntpUpdate");
    if (!EspApConfigurator.isConnected()) {
        DBLN(F("no network connection"));
        return;
    }

    // Find the IP of the timeserver
    dnsLookup();

    // If we have an IP for the timeserver, proceed
    if (_ntpServerIP == IPAddress()) {
        return;
    }

    // Clear previously RX packets
    while (_udp.parsePacket() > 0) {;}


    // Send a request
    sendNtpPacket();

    // TODO: re-write this in a non-blocking way?
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
        int size = _udp.parsePacket();
        if (size >= NTP_PACKET_SIZE) {
            DBLN(F("NTP RX"));
            _udp.read(_buf, NTP_PACKET_SIZE); // read packet into the buffer
            unsigned long secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 =  (unsigned long)_buf[40] << 24;
            secsSince1900 |= (unsigned long)_buf[41] << 16;
            secsSince1900 |= (unsigned long)_buf[42] << 8;
            secsSince1900 |= (unsigned long)_buf[43];
            
            unsigned long newUnix = secsSince1900 - 2208988800UL;
            int diff = newUnix - unixTime();
            _unixTime = newUnix;
            _lastNtpSuccess = Millis();
            DB(F("NTP success: "));
            DB(_unixTime);
            DB(F(" (diff="));
            DB(diff);
            DBLN(')');
            return;
        }
    }
    DBLN("NTP failed");
}

unsigned long ModeRealTime_::unixTime()
{
    if (_unixTime == 0) return 0;
    return _unixTime + ((Millis() - _lastNtpSuccess) / 1000);
}

String ModeRealTime_::isoTimestamp()
{
    return "YYYY-MM-DD HH:MM:SS ZON";
}

void ModeRealTime_::clearBuf()
{
    memset(_buf, 0, NTP_PACKET_SIZE * sizeof(byte));
}


bool ModeRealTime_::dnsLookup()
{
    DB(F("ModeRealTime::dnsLookup for "));
    DBLN(EspApConfigurator[SET_NTP_SERVER]->get());
    if (!WiFi.hostByName(EspApConfigurator[SET_NTP_SERVER]->get().c_str(), _ntpServerIP)) { // Get the IP address of the NTP server
        DB(F("DNS lookup failure for: "));
        DBLN(EspApConfigurator[SET_NTP_SERVER]->get());
        return false;
    } else {
        DB(F("DNS lookup success for: "));
        DB(EspApConfigurator[SET_NTP_SERVER]->get());
        DB(F(", IP: "));
        DBLN(_ntpServerIP);
        return true;
    }
}

void ModeRealTime_::sendNtpPacket()
{
    DBLN(F("ModeRealTime::sendNtpPacket"));

    clearBuf();

    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    _buf[0] = 0b11100011;   // LI, Version, Mode
    _buf[1] = 0;            // Stratum, or type of clock
    _buf[2] = 6;            // Polling Interval
    _buf[3] = 0xEC;         // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    _buf[12]  = 49;
    _buf[13]  = 0x4E;
    _buf[14]  = 49;
    _buf[15]  = 52;

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    _lastNtpAttempt = Millis();
    _udp.beginPacket(_ntpServerIP, 123); // port 123 = NTP
    _udp.write(_buf, NTP_PACKET_SIZE);
    _udp.endPacket();
}

