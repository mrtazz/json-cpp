include_directories(${PROJECT_SOURCE_DIR}/jsontestrunner)
add_executable(jsontestrunner main.cpp)

target_link_libraries(jsontestrunner jsoncpp)

add_test(NAME jsontestrunner_test 
    COMMAND ${PYTHON_EXECUTABLE}
    ${PROJECT_SOURCE_DIR}/test/runjsontests.py ${EXECUTABLE_OUTPUT_PATH}/jsontestrunner)
