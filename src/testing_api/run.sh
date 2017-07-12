#!/bin/sh

if [ "$1" = "" ]; then
    PYTHONPATH=$PWD/lib ./mpmtest --info
else
    PYTHONPATH=$PWD/lib ./mpmtest &
    sleep 0.5

    echo GET "http://localhost:8888/current_message?now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=0123456789&hmac=ab4725c8f7e9898d7bb1231a"
    GET "http://localhost:8888/current_message?now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=0123456789&hmac=ab4725c8f7e9898d7bb1231a"
    echo -e "\ncurl exit status=$?"; sleep 0.5

    echo POST upload
    curl -q -X POST --data "now=$(date +%s)&pubkey=1234567890&did=EA12F5&dkey=$RANDOM&hmac=ab4725c8f7e9898d7bb1231a&temperatureC=24.1&windspeedMs=1.2&moisture=0&rainfallMmHour=0.0&rainfallMmMinute=1.1&rainfallMmDay=3.5&batteryVoltage=4.45&latitude=52.123&longitude=-1.234" "http://localhost:8888/upload"
    echo -e "\ncurl exit status=$?"; sleep 0.5
    kill %%
fi

