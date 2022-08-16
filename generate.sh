#!/bin/sh

cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build