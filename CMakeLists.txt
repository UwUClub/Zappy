cmake_minimum_required(VERSION 3.13)  # CMake version check
project(zappy)               # Create project "simple_example"

# export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(gui)
add_subdirectory(server)
