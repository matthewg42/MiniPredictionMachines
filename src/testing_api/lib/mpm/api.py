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
PRIVATE_KEY = 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
PUBLIC_KEY = '1111111111'

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

@api.route('/upload', methods=['POST'])
def api_add():
    try:
        assert request.method == 'POST'
        validate_params(request.form)
        te = request.form['temperatureC']
        ws = request.form['windspeedMs']
        mo = request.form['moisture']
        rm = request.form['rainfallMmHour']
        rh = request.form['rainfallMmMinute']
        rd = request.form['rainfallMmDay']
        bv = request.form['batteryVoltage']
        la = request.form['latitude']
        lo = request.form['longitude']
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

    #if calc_hmac(params) != params['hmac']:
    #    messages.append("HMAC authentication failed")
    #    ok = False

    if not ok:
        raise Exception('; '.join(messages))

    return

