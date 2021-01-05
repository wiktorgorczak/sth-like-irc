#!/bin/bash

cd `dirname "$0"`
rm -rf server/build
rm -rf client/build
cd server
mkdir build
cd build
cmake -S ../ -B .
make
cd ../
cp *.ini ./build/
cd ../client
mkdir build
cd build
cmake -S ../ -B .
make

