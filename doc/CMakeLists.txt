set(documents
    ${PROJECT_SOURCE_DIR}/doc/footer.html
    ${PROJECT_SOURCE_DIR}/doc/header.html
    ${PROJECT_SOURCE_DIR}/doc/roadmap.dox
    ${PROJECT_SOURCE_DIR}/doc/CMakeLists.txt
    ${PROJECT_SOURCE_DIR}/doc/jsoncpp.dox
    ${PROJECT_SOURCE_DIR}/doc/doxyfile.in
    ${PROJECT_SOURCE_DIR}/doc/readme.txt)
set(DOCUMENT_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/testDocs)
add_custom_target(docs)
foreach(doc ${documents})
    add_custom_command(
        TARGET docs
        COMMAND ${CMAKE_COMMAND} -E
            copy ${doc} ${DOCUMENT_OUTPUT_PATH})
endforeach()

set_target_properties(docs PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

