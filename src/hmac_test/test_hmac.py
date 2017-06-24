#!/usr/bin/env python2.7
#
import hmac
import hashlib
import os

PRIKEY='12345678901234567890123456789012'
    
def calc_hmac(params):
    values = [str(v) for v in params.values()]
    values.sort()
    tohash = '&'.join(values) + '&'
    print("hashstr=\"%s\"" % tohash)
    return hmac.new(PRIKEY, tohash, digestmod=hashlib.sha256).hexdigest()

def do(params):
    print('hmac="%s"\n' % calc_hmac(params))

if __name__ == '__main__':
    do({'temperatore': 38.8, 'wiggles': 'a lot', 'butt': 'swipes'})
    
