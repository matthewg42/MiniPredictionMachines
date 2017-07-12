#include <MutilaDebug.h>
#include "HttpParamizer.h"

HttpParamizer::HttpParamizer(String url) :
    _baseUrl(url),
    _params(0)
{
}

void HttpParamizer::add(String name, String value)
{
    if (_params >= HTTP_PARAMIZER_MAX_PARAMS) {
        DBLN(F("HttpParamizer::add WARNING: too many params!"));
        return;
    }
    _paramNames[_params] = name;
    _paramValues[_params] = value;
    _params++;
}

void HttpParamizer::addHmac(String publicKey, String privateKey, String paramName)
{
    add(paramName, String(F("TODO")));
}

String HttpParamizer::getUrl()
{
    String u = _baseUrl;
    for (uint8_t i=0; i<_params; i++) {
        u += i == 0 ? '?' : '&';
        u += _paramNames[i];
        u += '=';
        u += _paramValues[i];
    }
    return u;
}


