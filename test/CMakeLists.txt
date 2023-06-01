cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(test_zappy
        testCommandGuiCli.cpp
        ../src/gui/cli/ClientApi.cpp
        ../src/gui/cli/ClientApi.hpp
        ../src/gui/cli/ServerData.cpp
        ../src/gui/cli/ServerData.hpp
        ../src/gui/cli/PlayerData.cpp
        ../src/gui/cli/PlayerData.hpp
        ../src/gui/cli/ParserData.cpp
        ../src/gui/cli/ParserData.hpp
        )

target_include_directories(test_zappy
        PRIVATE ../src/gui/cli
        )

target_link_libraries(test_zappy
        PRIVATE myproject::myproject_warnings
          myproject::myproject_options
          Catch2::Catch2WithMain
        )
