#! /bin/bash

avrdude -p m88 -P /dev/parport0 -c stk200 -e
