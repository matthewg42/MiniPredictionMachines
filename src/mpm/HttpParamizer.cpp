#include <string.h>
#include <MutilaDebug.h>
#include <Crypto.h>
#include "HttpParamizer.h"

HttpParamizer::HttpParamizer(String url) :
    _baseUrl(url),
    _paramCount(0)
{
}

void HttpParamizer::add(String name, String value)
{
    if (_paramCount >= HTTP_PARAMIZER_MAX_PARAMS) {
        DBLN(F("HttpParamizer::add WARNING: too many params!"));
        return;
    }
    _paramNames[_paramCount] = name;
    _paramValues[_paramCount] = value;
    _paramCount++;
}

void HttpParamizer::addHmac(const byte* privateKey, unsigned int privateKeyLen, String paramName)
{
    String sortedValues[HTTP_PARAMIZER_MAX_PARAMS];
    uint8_t count = 0;

    // Copy values, omiting existing hmac parameter
    for(uint8_t i=0; i<_paramCount; i++) {
        if (_paramNames[i] != paramName) {
            sortedValues[i] = _paramValues[i];
            count++;
        }
    }

    // Sort values - let's implement bubblesort, woohoo!
    bool swapped;
    do {
        swapped = false;
        for (uint8_t i=1; i<count; i++) {
            /* if this pair is out of order */
            if (sortedValues[i-1] > sortedValues[i]) {
                String tmp = sortedValues[i-1];
                sortedValues[i-1] = sortedValues[i];
                sortedValues[i] = tmp;
                swapped = true;
            }
        }
    } while (swapped);

    // Create hash string
    String hashString;
    for(uint8_t i=0; i<count; i++) {
        hashString += sortedValues[i];
        hashString += '&';
    }

    DB(F("HttpParamizer::addHmac hashStr="));
    DBLN(hashString);

    // HMAC calculation
    SHA256HMAC hmac(privateKey, privateKeyLen);
    hmac.doUpdate(hashString.c_str(), hashString.length());
    byte digest[SHA256_SIZE];
    hmac.doFinal(digest);
    String hexDigest;
    for (byte i=0; i<SHA256_SIZE; i++) {
        if (digest[i] < 0x10) { hexDigest += '0'; }
        hexDigest += String(digest[i], HEX);
    }
    add(paramName, hexDigest);
}

String HttpParamizer::getUrl()
{
    String u = _baseUrl;
    for (uint8_t i=0; i<_paramCount; i++) {
        u += i == 0 ? '?' : '&';
        u += _paramNames[i];
        u += '=';
        u += _paramValues[i];
    }
    return u;
}


