cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

add_executable(test_zappy
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

target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/core")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/implementation")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include/core")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/include/implementation")
target_include_directories(test_zappy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src/server/utils")

find_package(Catch2 REQUIRED)

target_link_libraries(test_zappy
        PRIVATE
          Catch2::Catch2WithMain
        )
