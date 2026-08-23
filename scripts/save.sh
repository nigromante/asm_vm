#!/usr/bin/env bash

clear
rm ../../demo.cast 
asciinema rec ../..demo.cast -c "$1 -f $2 -V -a"
agg ../../demo.cast ../../demo.gif

