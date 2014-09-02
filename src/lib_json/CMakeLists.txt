add_library( jsoncpp_lib ${JSONCPP_LIB_TYPE}
    json_tool.h
    json_reader.cpp
    json_batchallocator.h
    json_valueiterator.inl
    json_value.cpp
    json_writer.cpp
    version.h.in )
set_target_properties(jsoncpp_lib PROPERTIES PREFIX "")
set_target_properties( jsoncpp_lib PROPERTIES OUTPUT_NAME jsoncpp )
set_target_properties( jsoncpp_lib PROPERTIES
    VERSION ${JSON_CPP_VERSION}
    SOVERSION ${JSON_CPP_VERSION} )
# Install instructions for this target
install( TARGETS jsoncpp_lib
    RUNTIME DESTINATION build/bin
    LIBRARY DESTINATION build/lib
    ARCHIVE DESTINATION build/lib )
