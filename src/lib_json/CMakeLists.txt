set(headers
    json_tool.h
    json_batchallocator.h
    version.h)
set(sources
    json_reader.cpp
    json_value.cpp
    json_writer.cpp)
add_library(jsoncpp ${LIB_TYPE} ${sources} ${headers})
set_target_properties(jsoncpp PROPERTIES
    LINKER_LANGUAGE CXX)
