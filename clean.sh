#!/bin/bash
rm -rf CMakeCache.txt cmake_install.cmake Makefile CMakeFiles
rm -rf logger/CMakeFiles/ logger/cmake_install.cmake logger/Makefile logger/libLogger.a
rm -rf SYSLOG.txt
rm -rf packet_simulator/cmake_install.cmake  packet_simulator/libpacket_simulator.a packet_simulator/Makefile packet_simulator/CMakeFiles/
rm -rf firewall/cmake_install.cmake firewall/libfirewall.a firewall/Makefile firewall/CMakeFiles/
rm -rf eth_ip/cmake_install.cmake eth_ip/libeth_ip.a eth_ip/Makefile eth_ip/CMakeFiles/
rm -rf application/cmake_install.cmake application/libapplication.a application/Makefile application/CMakeFiles/
rm -rf PACKET_HANDLER
