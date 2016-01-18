cmake_minimum_required(VERSION 2.8.4)
project(time)

if(WIN32)
    set(source_files ${source_files} src/time_windows.c)
else()
    set(source_files ${source_files} src/time_unix.c)
endif()
add_executable(${PROJECT_NAME} ${source_files})
