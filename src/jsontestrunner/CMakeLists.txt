
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/src/lib_json")
include_directories("${PROJECT_SOURCE_DIR}/jsontestrunner")

find_package(PythonInterp REQUIRED)

add_executable(jsontestrunner main.cpp)

target_link_libraries(jsontestrunner jsoncpp)

add_test(
    NAME jsontestrunner_test
    COMMAND
        ${PYTHON_EXECUTABLE}
        "${PROJECT_SOURCE_DIR}/test/runjsontests.py"
        jsontestrunner)
