add_executable(zappy_gui
        main.cpp
        )

add_subdirectory(cli)

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cli")
