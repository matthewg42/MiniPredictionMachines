#!/bin/sh

if [ "$1" = "" ]; then
    PYTHONPATH=$PWD/lib ./mpmtest --info
else
    PYTHONPATH=$PWD/lib ./mpmtest &
    sleep 0.5
    for f in 1 2 3; do
        sleep 1
        echo "Testing get message"
        GET http://localhost:8888/api/message | od -tx1 -tc
    done
    curl -q -X POST --data 'temperatureC=24.1&windspeedMs=1.2&moisture=0&rainfallMmHour=0.0&rainfallMmMinute=1.1&rainfallMmDay=3.5&batteryVoltage=4.45' http://localhost:8888/api/add
    sleep 0.5 
    kill %%
fi

