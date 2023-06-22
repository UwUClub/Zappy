set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/input_parser.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/normalize_pos.c"
        )

add_subdirectory(game_logic)
add_subdirectory(gui)
add_subdirectory(player)
add_subdirectory(egg)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/game_logic")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/player")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gui")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/egg")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
