#pragma once

#include <stdint.h>

// Note: weather station has an ATMEGA328P, which is little endian
typedef struct {
    uint32_t sequenceNumber;
    float temperatureC;
    bool moisture;
    float windSpeedMs;
    float rainFallMmMinute;
    float rainFallMmHour;
    float rainFallMmDay;
    uint16_t checksum;
}__attribute__((packed, aligned(1))) WeatherPacket;

typedef union
{
    WeatherPacket data;
    uint8_t bytes[sizeof(WeatherPacket)];
} WeatherUnion;

uint16_t calcCrc16(void* ptr, uint8_t length);

// Update the checksum based on the other values in the packet
void weatherPacketCsUpdate(WeatherPacket *packet);

// Return true if the packet checks out OK, else false
bool weatherPacketCsTest(WeatherPacket *packet);

