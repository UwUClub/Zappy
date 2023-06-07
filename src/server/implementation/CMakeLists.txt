set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/input_parser.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_player.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/check_player_on_tile.c"
        )

add_subdirectory(gui)
add_subdirectory(player)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/player")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gui")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
