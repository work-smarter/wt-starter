#!/bin/bash

echo '------ BUILD -----'
mkdir -p build
cd build
cmake ..
make
echo '------ LIST FILES -----'
cd ..
ls -la .