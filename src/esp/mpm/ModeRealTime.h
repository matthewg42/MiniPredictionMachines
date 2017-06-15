#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Mode.h>

#define LOCAL_NTP_PORT      8888
#define NTP_PACKET_SIZE     48

//! \brief A real time class - set by NTP
class ModeRealTime_ : public Mode {
public:
    enum State {
        Wait,
        NtpWorking
    };

    ModeRealTime_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();
    unsigned long unixTime();

protected:
    unsigned long _lastNtpAttempt;
    unsigned long _lastNtpSuccess;
    unsigned long _unixTime;
    IPAddress _ntpServerIP;
    WiFiUDP _udp;
    byte _buf[NTP_PACKET_SIZE];   
    State _state;

    void ntpUpdate();
    void clearBuf();
    bool dnsLookup();
    void sendNtpPacket();
};

extern ModeRealTime_ ModeRealTime;

