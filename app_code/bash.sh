#!/bin/bash

mkdir build
cd build 
cmake ../
make

### Running the app
./gstreamer_01

### Cleaning the build dir for the next run (maybe not necessary, but just in case...)
cd ..
rm -r build