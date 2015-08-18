
include_directories("${PROJECT_SOURCE_DIR}/include/jsoncpp")
include_directories("${PROJECT_SOURCE_DIR}/test_lib_json")

find_package(PythonInterp REQUIRED)

add_executable(test_lib_json jsontest.cpp main.cpp)

target_link_libraries(test_lib_json jsoncpp)

# we need to run the tests such that they can find the library
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(test_path "PATH=$ENV{PATH};$<TARGET_FILE_DIR:jsoncpp>")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(test_path "DYLD_LIBRARY_PATH=$ENV{DYLD_LIBRARY_PATH}:$<TARGET_FILE_DIR:jsoncpp>")
else()
    set(test_path "DUMMY=")
endif()

add_test(
    NAME jsoncpp_test
    COMMAND
        ${CMAKE_COMMAND} -E env "${test_path}"
        ${PYTHON_EXECUTABLE}
        "${PROJECT_SOURCE_DIR}/test/rununittests.py"
        "$<TARGET_FILE:test_lib_json>")
