cmake_minimum_required(VERSION 2.8.12.2)

project(PACKET_HANDLER)

SET(CMAKE_CXX_FLAGS "-std=c++11")



option(LOG_FILE "crate log file" ON)
message(STATUS "create log file: ${LOG_FILE}")
add_executable(${PROJECT_NAME} Main.cpp)

add_subdirectory(firewall)
add_subdirectory(logger)
add_subdirectory(eth_ip)
add_subdirectory(application)
add_subdirectory(packet_simulator)
add_subdirectory(builder)


include_directories(firewall
                    logger
                    builder
                    eth_ip
                    application
                    packet_simulator
                    utils/Boost/binary/include
)

target_link_libraries(${PROJECT_NAME} Logger packet_simulator firewall)

execute_process(
    COMMAND git status
)

if (LOG_FILE)
    add_definitions(-DLOG_FILE)
endif (LOG_FILE)

#packages(not working linking error)
#set(Boost_NO_SYSTEM_PATHS ON)
#set(Boost_COMPONENTS system thread)
#set(BOOST_ROOT "utils/3rdParty/binary")
#set(BOOST_INCLUDEDIR "utils/3rdParty/binary")
#set(BOOST_LIBRARYDIR "utils/3rdParty/binary/libs")
#include_directories(${BOOST_INCLUDEDIR})
#find_package(Boost 1.75)
#link_libraries(BOOST_LIBRARYDIR)

