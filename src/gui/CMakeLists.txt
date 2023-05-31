include_directories(cli)

add_executable(zappy_gui
        main.cpp
        EventHandler.cpp
        CameraHandler.cpp
        FrameHandler.cpp
        cli/ClientApi.hpp
        cli/ClientApi.cpp
        cli/ParserData.hpp
        cli/ParserData.cpp
        cli/ServerData.hpp
        cli/Player.cpp
        cli/Player.hpp
        )

find_package(OGRE QUIET)

target_link_libraries(zappy_gui
    PRIVATE myproject::myproject_options
        myproject::myproject_warnings
        OgreBites
        OgreRTShaderSystem
)

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cli")
target_include_directories(zappy_gui PRIVATE "${OGRE_INCLUDE_DIRS}")

set_target_properties(zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
