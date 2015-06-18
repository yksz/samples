cmake_minimum_required(VERSION 2.8.4)
project(echo_server C)

option(WIN "Build for windows" OFF)

if(WIN)
    set(SOURCE_FILES ${SOURCE_FILES} src/echo_server_windows.c)
else()
    set(SOURCE_FILES ${SOURCE_FILES} src/echo_server_unix.c)
    add_definitions(-Wall -std=c99)
endif()
add_executable(echo_server ${SOURCE_FILES})
