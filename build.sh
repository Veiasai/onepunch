#!/bin/bash

if [[ ! -d "build" ]]
then 
    mkdir build
    mkdir build/debug
    mkdir build/release
fi

cmake -DCMAKE_BUILD_TYPE=Debug -S src -B build/debug

cmake -DCMAKE_BUILD_TYPE=Release -S src -B build/release