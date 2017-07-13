#pragma once

#include <Arduino.h>
#include "Config.h"

class HttpParamizer {
public:
    HttpParamizer(String url);
    void add(String name, String value);
    void addHmac(const byte* privateKey, unsigned int privateKeyLen, String paramName);
    String getUrl();

private:
    String _baseUrl;
    uint8_t _paramCount;
    String _paramNames[HTTP_PARAMIZER_MAX_PARAMS];
    String _paramValues[HTTP_PARAMIZER_MAX_PARAMS];

};

