find_package(OGRE QUIET)
if (OGRE_FOUND)
    message(STATUS "GUI: ON")
    add_subdirectory(gui)
else()
    message(STATUS "GUI: OFF")
    message(STATUS "NO_CONNECTION: ${NO_CONNECTION}")
    message(STATUS "OGRE_FOUND: ${OGRE_FOUND}")
    execute_process(
            COMMAND touch zappy_gui
    )
endif()

add_subdirectory(server)