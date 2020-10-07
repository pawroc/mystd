cmake_minimum_required(VERSION 3.16)

project(String LANGUAGES CXX
               VERSION 0.0.1
               DESCRIPTION "Simpler implementation of std::string")


#######################
# include | find_package search path
#
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


########################
# Compiler settings
#
include(compiler_options)


########################
# Options
#
option(BUILD_UT "Builds UTs" OFF)


########################
# Targets
#
set(SOURCES src/string.cpp)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc> # <prefix>/include
    PRIVATE src)

include(unit_tests)
