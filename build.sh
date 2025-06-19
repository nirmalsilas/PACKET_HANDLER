#!/bin/bash
rm -rf CMakeCache.txt cmake_install.cmake Makefile CMakeFiles
rm -rf logger/CMakeFiles/ logger/cmake_install.cmake Makefile
rm -rf SYSLOG.txt
rm -rf packet_simulator/cmake_install.cmake  packet_simulator/libpacket_simulator.a packet_simulator/Makefile packet_simulator/CMakeFiles/
cmake -S . -B .
make
