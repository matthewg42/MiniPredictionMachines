#include <stddef.h>
#include "Crc16.h"
#include "WeatherPacket.h"

uint16_t calcCrc16(void* ptr, uint8_t length)
{
    Crc16 crc; 
    crc.clearCrc();
    uint8_t* bytes = (uint8_t*)ptr;

    // Calculate CRC up to but not including CRC value
    for(uint8_t i=0; i<offsetof(WeatherPacket, checksum); i++) {
        crc.updateCrc(bytes[i]);
    }

    return crc.getCrc();
}

// update the checksum based on the other values in the packet
void weatherPacketCsUpdate(WeatherPacket* packet)
{
    if (!packet) return;
    packet->checksum = calcCrc16((uint8_t*)packet, sizeof(WeatherPacket));
}

// Return true if the packet checks out OK, else false
bool weatherPacketCsTest(WeatherPacket* packet)
{
    if (!packet) return false;
    uint16_t check = calcCrc16((uint8_t*)packet, sizeof(WeatherPacket));
    return check == packet->checksum;
}

