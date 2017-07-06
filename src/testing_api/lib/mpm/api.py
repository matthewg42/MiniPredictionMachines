import json
import socket
import os
import logging
import subprocess
import jsonmerge
import random
from mpm.util import json_resp
from flask import Blueprint, render_template, Response, request

log = logging

api = Blueprint('api', __name__)

messages = ['It\'s not that easy being green',
'Having to spend each day the color of the leaves.',
'When I think it could be nicer being red, or yellow or gold-',
'or something much more colorful like that.',
'It seems you blend in with so many other ordinary things.',
'And people tend to pass you over \'cause you\'re not standing out like flashy sparkles in the water- or stars in the sky.']

# net API route implementations
@api.route('/current_message', methods=['GET'])
def api_message():
    return(messages[random.randint(0,len(messages)-1)])

@api.route('/upload', methods=['POST'])
def api_add():
    try:
        assert request.method == 'POST'
        te = request.form['temperatureC']
        ws = request.form['windspeedMs']
        mo = request.form['moisture']
        rm = request.form['rainfallMmHour']
        rh = request.form['rainfallMmMinute']
        rd = request.form['rainfallMmDay']
        bv = request.form['batteryVoltage']
        print('api_add SUCCESS TE=%s WS=%s MO=%s RM=%s RH=%s RD=%s BV=%s' % (
                te, ws, mo, rm, rh, rd, bv )) 
    except Exception as e:
        return(json_resp({"error":"Internal server error", "message": "%s : %s" % (type(e), str(e))}, 400))
    return(json_resp({'status': 'ok'}))


