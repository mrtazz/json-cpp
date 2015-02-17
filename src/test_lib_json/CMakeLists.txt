
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/test_lib_json")

set_python()

add_executable(test_lib_json jsontest.cpp main.cpp)

target_link_libraries(test_lib_json jsoncpp)

add_test(
    NAME jsoncpp_test
    COMMAND
        ${PYTHON_EXECUTABLE}
        "${PROJECT_SOURCE_DIR}/test/rununittests.py"
        test_lib_json)
