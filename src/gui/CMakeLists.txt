find_package(OGRE QUIET)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -O2")

add_executable(zappy_gui
        main.cpp
        App.cpp
        App+Listener.cpp
        Button.cpp
        Mediator.cpp
        Observer.cpp
        SceneBuilder.cpp
        )

find_package(OGRE QUIET)

target_link_libraries(zappy_gui
    PRIVATE myproject::myproject_options
        myproject::myproject_warnings
        ${OGRE_LIBRARIES}
)

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cli")
target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(zappy_gui PRIVATE "${OGRE_INCLUDE_DIRS}")

add_subdirectory(cli)
add_subdirectory(handlers)

set_target_properties(zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
