message("Configureing json-cpp")
cmake_minimum_required(VERSION 2.8.3)
project(jsoncpp)
set(MBCMakeTools_DIR ${PROJECT_SOURCE_DIR}/../../mw-cmake-tools/)
find_package(
    MBCMakeTools
    REQUIRED)
setup_environment()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions("/D Win32")
endif()
add_compiler_flags()
set_shared(true)

install_headers(${PROJECT_SOURCE_DIR}/include/)

include_directories(${INCLUDE_OUTPUT_PATH}/jsoncpp)
include_directories(src/lib_json)
add_subdirectory(src/lib_json)
add_subdirectory(doc)
