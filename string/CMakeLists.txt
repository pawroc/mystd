cmake_minimum_required(VERSION 3.16)

project(String LANGUAGES CXX
               VERSION 0.0.1
               DESCRIPTION "Simpler implementation of std::string")

           #include(compiler_options.cmake)

option(BUILD_UT "Builds UTs" OFF)

set(SOURCES src/string.cpp)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc> # <prefix>/include
    PRIVATE src)

if(BUILD_UT STREQUAL "ON")
    message("::: Building Unit Tests")
    enable_testing()
    add_subdirectory(tst)
endif()
