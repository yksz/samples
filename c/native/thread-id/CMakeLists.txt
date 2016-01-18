cmake_minimum_required(VERSION 2.8.4)
project(tid)

set(source_files ${source_files} src/tid.c)
add_executable(${PROJECT_NAME} ${source_files})
