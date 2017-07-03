#!/bin/sh

PYTHONPATH=$PWD/lib ./mpmtest --info &

for f in 1 2 3; do
    sleep 1
    echo "Testing get message"
    curl http://localhost:8888/api/message | od -tx1 -tc
done

curl -H "Content-Type: application/json" -X POST -d '{"ap":{"enabled":true}}' http://localhost/api/net/config


kill %%

