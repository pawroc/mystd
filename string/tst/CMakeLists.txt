cmake_minimum_required(VERSION 3.16)

set(TEST_EXECUTABLE_NAME "${PROJECT_NAME}_UT")
set(SOURCES test_string.cpp)

add_executable(${TEST_EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${TEST_EXECUTABLE_NAME} gtest gmock gtest_main gmock_main ${PROJECT_NAME})

add_test(NAME "${TEST_EXECUTABLE_NAME}"
         COMMAND ${TEST_EXECUTABLE_NAME})
