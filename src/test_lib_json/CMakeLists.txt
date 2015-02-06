
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/test_lib_json")

use_api(JSON_API)

add_executable(test_lib_json jsontest.cpp main.cpp)

target_link_libraries(test_lib_json jsoncpp)

add_test(NAME jsoncpp_test
    COMMAND ${PYTHON_EXECUTABLE}
    ${PROJECT_SOURCE_DIR}/test/rununittests.py ${EXECUTABLE_OUTPUT_PATH}/test_lib_json)
