
cmake_minimum_required(VERSION 3.1.0)

project(jsoncpp CXX)

find_package(MBCMakeTools REQUIRED NO_POLICY_SCOPE)

add_subdirectory(src/lib_json)
add_subdirectory(doc)

enable_testing()
add_subdirectory(src/jsontestrunner)

if(NOT ${MB_BT_PLATFORM} MATCHES "Ubuntu_[0-9]*_32")
    add_subdirectory(src/test_lib_json)
endif()

