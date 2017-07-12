import json
import re
from flask import Response
from datetime import datetime

pretty_json = True

def json_dump(j):
    if pretty_json:
        return json.dumps(j, indent=4, separators=(',', ': '), sort_keys=True)
    else:
        return json.dumps(j)

def nocache(response):
    response.headers['Last-Modified'] = datetime.now()
    response.headers['Cache-Control'] = 'no-store, no-cache, must-revalidate, post-check=0, pre-check=0, max-age=0'
    response.headers['Pragma'] = 'no-cache'
    response.headers['Expires'] = '-1'
    return response

def json_resp(j, status=200):
    return(nocache(Response(response=json_dump(j),
                    status=status,
                    mimetype="application/json")))

def plaintext_resp(text, status=200):
    return(nocache(Response(response=text,
                    status=status,
                    mimetype="application/plain")))


