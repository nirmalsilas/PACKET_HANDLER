file(GLOB SOURCE_FILES
    *.cpp
)
include_directories(${PROJECT_SOURCE_DIR}/logger
${PROJECT_SOURCE_DIR}/builder

)
add_library(firewall ${SOURCE_FILES})