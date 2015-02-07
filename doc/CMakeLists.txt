
# json-cpp has some fancy doxygen setup, so we just use their script
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxybuild)
    set_target_properties(
        doxybuild
        PROPERTIES
        EXCLUDE_FROM_DEFAULT_BUILD TRUE)

    add_custom_command(
        TARGET doxybuild
        COMMAND
            python "${PROJECT_SOURCE_DIR}/doxybuild.py"
            --doxygen=${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        VERBATIM)

    install_docs(
        DIRECTORY "${PROJECT_SOURCE_DIR}/dist/doxygen"
        PREFIX jsoncpp/doxygen
        DEPENDS doxybuild)
endif()

install_docs(
    FILES "${PROJECT_SOURCE_DIR}/doc/readme.txt"
    PREFIX jsoncpp)
