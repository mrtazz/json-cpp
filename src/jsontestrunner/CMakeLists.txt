
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/src/lib_json")
include_directories("${PROJECT_SOURCE_DIR}/jsontestrunner")

add_compiler_flags()

find_package(PythonInterp REQUIRED)

add_executable(jsontestrunner main.cpp)

target_link_libraries(jsontestrunner jsoncpp)

# we need to run the tests such that they can find the library
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(test_path "$ENV{PATH};$<TARGET_FILE_DIR:jsoncpp>")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(test_path "$ENV{DYLD_LIBRARY_PATH}:$<TARGET_FILE_DIR:jsoncpp>")
endif()

add_test(
    NAME jsontestrunner_test
    COMMAND
        ${CMAKE_COMMAND} -E env "PATH=${test_path}"
        ${PYTHON_EXECUTABLE}
        "${PROJECT_SOURCE_DIR}/test/runjsontests.py"
        "$<TARGET_FILE:jsontestrunner>" "${PROJECT_SOURCE_DIR}/test/data")
