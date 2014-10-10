cmake_minimum_required(VERSION 2.6)
message("Configureing json-cpp")
project(jsoncpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions("/D Win32")
endif()
add_compiler_flags()
set_shared(true)

install_headers(${PROJECT_SOURCE_DIR}/include/)

include_directories(${INCLUDE_OUTPUT_PATH}/jsoncpp)
include_directories(src/lib_json)
add_subdirectory(src/lib_json)
