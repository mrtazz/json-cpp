
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/src/lib_json")
include_directories("${PROJECT_SOURCE_DIR}/jsontestrunner")

find_package(PythonInterp REQUIRED)

add_executable(jsontestrunner main.cpp)
use_standard_flags(jsontestrunner)
target_link_libraries(jsontestrunner jsoncpp)

# we need to run the tests such that they can find the library
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(test_path "PATH=$ENV{PATH};$<TARGET_FILE_DIR:jsoncpp>")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(test_path "DYLD_LIBRARY_PATH=$ENV{DYLD_LIBRARY_PATH}:$<TARGET_FILE_DIR:jsoncpp>")
else()
    set(test_path "LD_LIBRARY_PATH=$<TARGET_FILE_DIR:jsoncpp>:$ENV{DYLD_LIBRARY_PATH}")
endif()

add_test(
    NAME jsontestrunner_test
    COMMAND
        ${CMAKE_COMMAND} -E env "${test_path}"
        ${PYTHON_EXECUTABLE}
        "${PROJECT_SOURCE_DIR}/test/runjsontests.py"
        "$<TARGET_FILE:jsontestrunner>" "${PROJECT_SOURCE_DIR}/test/data")
