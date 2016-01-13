cmake_minimum_required(VERSION 2.8.4)
project(mac)

if(WIN32)
    set(source_files ${source_files} src/mac_windows.c)
else()
    set(source_files ${source_files} src/mac_unix.c)
endif()
add_executable(${PROJECT_NAME} ${source_files})
