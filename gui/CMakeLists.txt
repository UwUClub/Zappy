cmake_minimum_required(VERSION 3.13)  # CMake version check
set(PROJECT_NAME gui)
project(${PROJECT_NAME})            # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++14 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

include_directories(src)
include_directories(src/cli)

set(SOURCE_FILES
    src/main.cpp
    src/cli/ClientApi.cpp
    src/cli/ClientApi.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    COMPILE_FLAGS ""
)
