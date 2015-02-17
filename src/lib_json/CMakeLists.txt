
set(headers
    json_tool.h
    json_batchallocator.h
    version.h)
set(sources
    json_reader.cpp
    json_value.cpp
    json_writer.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/src/lib_json")

add_compiler_flags()

add_library(jsoncpp SHARED ${sources} ${headers})

export_api(jsoncpp JSON_API)

install_config(
    NAME JsonCpp
    TARGET jsoncpp)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/jsoncpp"
    DESTINATION "${HEADER_INSTALL_DESTINATION}")
