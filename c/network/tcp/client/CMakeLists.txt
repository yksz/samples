cmake_minimum_required(VERSION 2.8.4)
project(client C)

if(WIN32)
    set(source_files ${source_files} src/client_windows.c)
else()
    set(source_files ${source_files} src/client_unix.c)
    add_definitions(-Wall -std=c99)
endif()
add_executable(${PROJECT_NAME} ${source_files})
