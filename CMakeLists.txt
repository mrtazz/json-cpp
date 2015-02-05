
cmake_minimum_required(VERSION 2.8.3)

project(jsoncpp CXX)

find_package(
    MBCMakeTools
    REQUIRED)

# TODO(ted): figure out if this is needed
# if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # add_definitions("/D Win32")
# endif()

add_subdirectory(src/lib_json)
add_subdirectory(doc)
