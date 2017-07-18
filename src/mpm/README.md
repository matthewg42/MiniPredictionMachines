Hardware Config
===============

HC12 device must be in FU2/4800 BAUD mode.

Building
========

Create a file called Makefile.apikeys in this directory containing the following:

    BUILD_EXTRA_FLAGS += -DTIMESTREAMS_API_PUBKEY='"xxxxxxxxxx"'
    BUILD_EXTRA_FLAGS += -DTIMESTREAMS_API_PRIKEY='"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"'

...with values from your timestreams account. This file will not be added to the gitrepository for security reasons.

If you do not use the Makefile build system, edit Config.h and add the following:

#define TIMESTREAMS_API_PUBKEY "xxxxxxxxxx"
#define TIMESTREAMS_API_PRIKEY "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"

