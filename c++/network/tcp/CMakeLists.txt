cmake_minimum_required(VERSION 2.8.4)
project(tcp CXX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(source_files
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/socket.cpp
    ${PROJECT_SOURCE_DIR}/src/thread_pool.cpp
)
if(WIN32)
    set(source_files ${source_files}
        ${PROJECT_SOURCE_DIR}/src/windows/client_windows.cpp
        ${PROJECT_SOURCE_DIR}/src/windows/server_windows.cpp
        ${PROJECT_SOURCE_DIR}/src/windows/socket_windows.cpp
    )
else()
    set(source_files ${source_files}
        ${PROJECT_SOURCE_DIR}/src/unix/client_unix.cpp
        ${PROJECT_SOURCE_DIR}/src/unix/server_unix.cpp
        ${PROJECT_SOURCE_DIR}/src/unix/socket_unix.cpp
    )
endif()
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/windows
    ${PROJECT_SOURCE_DIR}/src/unix
)

add_subdirectory(client)
add_subdirectory(server)
