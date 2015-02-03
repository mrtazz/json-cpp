
cmake_minimum_required(VERSION 2.8.3)

project(jsoncpp CXX)

find_package(
    MBCMakeTools
    REQUIRED)

include_directories(${INCLUDE_OUTPUT_PATH}/jsoncpp)
include_directories(src/lib_json)

enable_testing()
add_subdirectory(src/jsontestrunner)
add_subdirectory(src/test_lib_json)

add_subdirectory(src/lib_json)
add_subdirectory(doc)

