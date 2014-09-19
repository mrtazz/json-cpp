cmake_minimum_required(VERSION 2.6)
message("Configureing json-cpp")
project(jsoncpp)

set_shared(true)

file(INSTALL
    DIRECTORY include/jsoncpp
    DESTINATION ${INCLUDE_OUTPUT_PATH}
    FILES_MATCHING PATTERN "*.h")
    
include_directories(${INCLUDE_OUTPUT_PATH})
include_directories(src/lib_json)
add_subdirectory(src/lib_json)

