cmake_minimum_required(VERSION 2.6)
project(json-cpp)
option(JSONCPP_LIB_BUILD_SHARED "Build jsoncpp_lib as a shared library." OFF)
if(JSONCPP_LIB_BUILD_SHARED)
  set(JSONCPP_LIB_TYPE SHARED)
  add_definitions( -DJSON_DLL_BUILD )
else()
  set(JSONCPP_LIB_TYPE STATIC)
endif()

include_directories(include/jsoncpp)
include_directories(src/lib_json)
add_subdirectory(src/lib_json)

