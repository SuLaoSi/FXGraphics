#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

cd ./build
cmake ..


read -p "Press Enter to continue:"

