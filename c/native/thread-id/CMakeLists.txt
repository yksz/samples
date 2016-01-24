cmake_minimum_required(VERSION 2.8.4)
project(tid)

add_definitions(-Wall -std=c++11)

set(source_files ${source_files} src/tid.cpp)
add_executable(${PROJECT_NAME} ${source_files})
