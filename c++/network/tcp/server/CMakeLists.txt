# pthread
if(UNIX) # include Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(source_files ${source_files}
    main.cpp
)
add_executable(${PROJECT_NAME}-server ${source_files})
