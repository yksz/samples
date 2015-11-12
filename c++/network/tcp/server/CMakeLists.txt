cmake_minimum_required(VERSION 2.8.4)
project(server CXX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(source_files
    src/main.cpp
    src/thread_pool.cpp
)
if(WIN32)
    set(source_files ${source_files}
        src/server_win.cpp
        src/socket_win.cpp
    )
else()
    set(source_files ${source_files}
        src/server_unix.cpp
        src/socket_unix.cpp
    )
endif()
include_directories(
    ${PROJECT_SOURCE_DIR}/src
)
# pthread
if(UNIX) # include Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
add_executable(${PROJECT_NAME} ${source_files})
