import json
import socket
import os
import logging
import subprocess
import jsonmerge
import random
import hmac
import hashlib
import time
from mpm.util import plaintext_resp
from flask import Blueprint, render_template, Response, request

log = logging

api = Blueprint('api', __name__)
PRIVATE_KEY = os.environ['MPM_API_PRIVATE_KEY']

messages = ['It\'s not that easy being green',
'Having to spend each day the color of the leaves.',
'When I think it could be nicer being red, or yellow or gold-',
'or something much more colorful like that.',
'It seems you blend in with so many other ordinary things.',
'And people tend to pass you over \'cause you\'re not standing out like flashy sparkles in the water- or stars in the sky.',
'Sitting quietly and looking wise, isn\'t nearly as good, as drinking wine and making a riotous shouting',
'All your API calls are belong to us.',
'Spurden or Thing?',
'An empty list is a sorted list']

# net API route implementations
@api.route('/current_message', methods=['GET'])
def api_message():
    try:
        validate_params(request.args)
        # Format: e|message
        # Where: 
        #  e       = expiry time expressed as unix seconds
        #  message = message in ASCII
        if random.randint(0,10) == 1:
            expiry = int(time.time()) + random.randint(5,300)
            message = messages[random.randint(0,len(messages)-1)]
            return(plaintext_resp("%s|%s" % (expiry, message)))
        else:
            return(plaintext_resp(""))
    except Exception as e:
        return(plaintext_resp('ERROR: %s' % str(e), 400))

@api.route('/upload', methods=['POST', 'GET'])
def api_add():
    try:
        # assert request.method == 'POST'
        params = request.args if request.method == 'GET' else request.form
        validate_params(params)
        te = params['temperatureC']
        ws = params['windspeedMs']
        mo = params['moisture']
        rm = params['rainfallMmHour']
        rh = params['rainfallMmMinute']
        rd = params['rainfallMmDay']
        bv = params['batteryVoltage']
        la = params['latitude']
        lo = params['longitude']
        print('api_add SUCCESS TE=%s WS=%s MO=%s RM=%s RH=%s RD=%s BV=%s LA=%s LO=%s' % (
                te, ws, mo, rm, rh, rd, bv, la, lo )) 
    except Exception as e:
        return(plaintext_resp('ERROR: %s' % str(e), 400))
    return(plaintext_resp('ok'))

def calc_hmac(params):
    values = [str(v) for k, v in params.items() if k != 'hmac']
    values.sort()
    print("values to hash: %s" % repr(values))
    tohash = '&'.join(values) + '&' 
    print("string to hash: %s" % tohash)
    hmachex = hmac.new(PRIVATE_KEY.encode(), tohash.encode(), digestmod=hashlib.sha256).hexdigest()
    print("hmac: %s" % hmachex)
    return hmachex

def validate_params(params):
    ok = True
    messages = []
    for p in ['now', 'pubkey', 'did', 'hmac']:
        if p not in params:
            messages.append(p)
            ok = False

    if not ok:
        raise Exception('Missing expected param(s): %s' % ', '.join(messages))
    
    try:
        n = int(params['now'])
    except Exception as e:
        messages.append("param 'now' is not integer")
        ok = False

    if len(params['did']) != 6:
        messages.append("param 'did' should be 6 characters long")
        ok = False

    h = calc_hmac(params)
    if h != params['hmac']:
        messages.append("HMAC authentication failed\ngot: %s\nexp: %s" % (params['hmac'], h))
        ok = False

    if not ok:
        raise Exception('; '.join(messages))

    return

