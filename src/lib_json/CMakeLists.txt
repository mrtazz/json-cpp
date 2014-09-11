set(headers
    json_tool.h
    json_batchallocator.h
    version.h.in )
set(set
    json_reader.cpp
    json_valueiterator.inl
    json_value.cpp
    json_writer.cpp
    )
add_library( jsoncpp ${LIB_TYPE} ${sources} ${headers})
set_target_properties( jsoncpp PROPERTIES 
    LINKER_LANGUAGE CXX)


