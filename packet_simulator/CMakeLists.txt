file(GLOB SOURCE_FILES
    *.cpp
)
include_directories(${PROJECT_SOURCE_DIR}/utils/Boost/binary/include
                    ${PROJECT_SOURCE_DIR}/logger
)
add_library(packet_simulator ${SOURCE_FILES})
