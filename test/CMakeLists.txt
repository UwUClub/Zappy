cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_subdirectory(./gui)
add_subdirectory(./server)
