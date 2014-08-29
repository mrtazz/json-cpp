set( JSONCPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/jsoncpp )

set( PUBLIC_HEADERS
    ${JSONCPP_INCLUDE_DIR}/json/config.h
    ${JSONCPP_INCLUDE_DIR}/json/forwards.h
    ${JSONCPP_INCLUDE_DIR}/json/features.h
    ${JSONCPP_INCLUDE_DIR}/json/value.h
    ${JSONCPP_INCLUDE_DIR}/json/reader.h
    ${JSONCPP_INCLUDE_DIR}/json/writer.h
    ${JSONCPP_INCLUDE_DIR}/json/assertions.h
    ${JSONCPP_INCLUDE_DIR}/json/version.h )

source_group( "Public API" FILES ${PUBLIC_HEADERS} )

add_library( jsoncpp_lib ${JSONCPP_LIB_TYPE}
    ${PUBLIC_HEADERS}
    json_tool.h
    json_reader.cpp
    json_batchallocator.h
    json_valueiterator.inl
    json_value.cpp
    json_writer.cpp
    version.h.in )
set_target_properties( jsoncpp_lib PROPERTIES OUTPUT_NAME jsoncpp )
set_target_properties( jsoncpp_lib PROPERTIES
    VERSION ${JSON_CPP_VERSION}
    SOVERSION ${JSON_CPP_VERSION} )
# Install instructions for this target
install( TARGETS jsoncpp_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib )
