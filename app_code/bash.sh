#!/bin/bash


mkdir build
cd build 
cmake ../
make

rm -r /app_code/tmp/tmpsock*

./gstreamer_01