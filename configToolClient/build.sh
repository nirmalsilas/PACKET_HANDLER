#!/bin/bash
rm -rf CMakeCache.txt cmake_install.cmake Makefile CMakeFiles configtoolClient
cmake -S . -B .
make
