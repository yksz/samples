cmake_minimum_required(VERSION 2.8.4)
project(client CXX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(source_files
    src/main.cpp
)
if(WIN32)
    set(source_files ${source_files}
        src/client_windows.cpp
    )
else()
    set(source_files ${source_files}
        src/client_unix.cpp
    )
endif()
include_directories(
    ${PROJECT_SOURCE_DIR}/src
)
add_executable(${PROJECT_NAME} ${source_files})
