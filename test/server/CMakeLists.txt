cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(test_zappy_server
        normalizePos.cpp
        isPlayer.cpp
        getPlayerById.cpp
        calcOutbound.cpp
        intToS.cpp
        revStr.cpp
        concatStr.cpp
        concatWordArray.cpp
        isInt.cpp
        isIp.cpp
        )

target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/core")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/implementation")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include/core")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include/implementation")
target_include_directories(test_zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/utils")

target_include_directories(test_zappy_server
        PRIVATE ../../src/gui/cli
        ../../src/gui
        )

target_link_libraries(test_zappy_server
        PRIVATE myproject::myproject_warnings
          myproject::myproject_options
          Catch2::Catch2WithMain
        )
