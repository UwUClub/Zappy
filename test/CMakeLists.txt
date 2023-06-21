cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(test_zappy
        testCommandGuiCli.cpp
        ../src/gui/App.cpp
        ../src/gui/App+Listener.cpp
        ../src/gui/Button.cpp
        ../src/gui/Inventory.cpp
        ../src/gui/Mediator.cpp
        ../src/gui/Observer.cpp
        ../src/gui/SceneBuilder.cpp
        ../src/gui/handlers/events/CameraHandler.cpp
        ../src/gui/handlers/events/InputHandler.cpp
        ../src/gui/handlers/events/ClickHandler.cpp
        ../src/gui/handlers/AnimationHandler.cpp
        ../src/gui/cli/ClientApi.cpp
        ../src/gui/cli/ClientApi+Listener.cpp
        ../src/gui/cli/ItemPacket.cpp
        ../src/gui/cli/ParserData.cpp
        ../src/gui/cli/PlayerData.cpp
        ../src/gui/cli/EggData.cpp
        )

target_include_directories(test_zappy
        PRIVATE ../src/gui/cli
        ../src/gui
        ../src/gui/handlers/events
        ../src/gui/handlers
        )

target_link_libraries(test_zappy
        PRIVATE myproject::myproject_warnings
          myproject::myproject_options
          Catch2::Catch2WithMain
          ${OGRE_LIBRARIES}
        )
