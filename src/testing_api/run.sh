#!/bin/sh

if [ "$1" = "" ]; then
    PYTHONPATH=$PWD/lib ./mpmtest --info
else
    PYTHONPATH=$PWD/lib ./mpmtest &
    sleep 0.5

    echo GET /register
    GET "http://localhost:8888/register?now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=$RANDOM&hmac=ab4725c8f7e9898d7bb1231a" 
    sleep 0.5

    echo GET /current_message
    GET "http://localhost:8888/current_message?now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=$RANDOM&hmac=ab4725c8f7e9898d7bb1231a"
    echo ""

    echo POST upload
    curl -q -X POST --data "now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=$RANDOM&hmac=ab4725c8f7e9898d7bb1231a&temperatureC=24.1&windspeedMs=1.2&moisture=0&rainfallMmHour=0.0&rainfallMmMinute=1.1&rainfallMmDay=3.5&batteryVoltage=4.45" "http://localhost:8888/upload"
    sleep 0.5 
    kill %%
fi

