Rain Gauge Calibration
======================

I determinted empirically (using a syringe with accurate graduations, and manually counting pulses), that the rain gauge creates 23 pulses for every 40ml of water which enters the sensor.  Each pulse is therefore equal to a water collection of: 

    40 / 23 = 1.739 ml

I shall call this Vp, or nomincal volume per pulse. 

The collection are for this rain gauge is a rectangle with rounded corners, with the following dimensions:

    length, l = 109.75 mm
    width, w = 49.7 mm
    corner radius, r = 4.7 mm

The area, A of a rectangle with rounded corners is calcuated thus:

    A = (l * w) - ((4-pi)*r*r)
    A ~= 5436 sq. mm


A litre of water is a cube with sides 100 mm. The area of one side of this cube is 10000 sq. mm.

One ml of water spread over 10000 sq. mm would fill a depth of 0.1 mm. (check, 100/0.1 = 1000ml in a litre).

One ml of water would fill a volume with cross sectional area A (A in sq.mm) to a depth of:

    1000/A mm

For the rain gauge, 1 ml of water therefore corresponds to a depth per ml, Dm:

    Dm = 1000 / 5436 = 0.18395879323031640912 mm of rain.

Each pulse corresponds to a depth per pulse, Dp:

    Dp = Dm * Vp
    Dp = 0.319951 mm


Rainfalls is typically measured over several periods of time:

Typical rainfall in the midlands for a rainy day is 5.4 mm over the course of the day.  Let's assume this corresponds to 4 hours of rain, we expect something of the order of 1.4 mm / hour for average rain.

So in "average" rain, we can expect 4-5 pulses an hour.  Wow, not so much.  Def glad I de-bounced!


