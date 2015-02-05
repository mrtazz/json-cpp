
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

add_api(JSON_API)

add_compiler_flags()

# in other projects we use add_api(), but json already had their api set up
add_definitions("\"-DJSON_DLL_BUILD\"")

add_library(jsoncpp SHARED ${sources} ${headers})

install_config(
    NAME JsonCpp
    TARGET jsoncpp
    API JSON_API)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/jsoncpp"
    DESTINATION ${HEADER_INSTALL_DESTINATION})
