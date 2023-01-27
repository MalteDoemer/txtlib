#!/bin/sh

cmake -DCOMPILE_EXAMPLES=OFF -DCOMPILE_TESTS=OFF -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build