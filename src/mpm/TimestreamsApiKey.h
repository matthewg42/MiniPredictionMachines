#pragma once

// #include <string.h>
#include <Arduino.h>
#include <Config.h>

const char* TimestreamsApiPriKeySigned = TIMESTREAMS_API_PRIKEY;

const byte* TimestreamsApiPriKey() {
    return (const byte*)TimestreamsApiPriKeySigned;
}

unsigned int TimestreamsApiPriKeyLen() {
    return strlen(TimestreamsApiPriKeySigned);
}

