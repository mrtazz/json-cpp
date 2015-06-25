
set(headers
    json_tool.h
    json_batchallocator.h
    version.h)
set(sources
    json_reader.cpp
    json_value.cpp
    json_writer.cpp)

add_compiler_flags()

add_library(jsoncpp SHARED ${sources} ${headers})

target_include_directories(
    jsoncpp
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/jsoncpp>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/lib_json>
        $<INSTALL_INTERFACE:${HEADER_INSTALL_DIR}>)

export_api(jsoncpp JSON_API)

generate_and_install_config(
    NAME JsonCpp
    TARGETS jsoncpp)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/jsoncpp"
    DESTINATION "${HEADER_INSTALL_DIR}")
