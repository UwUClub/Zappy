set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/incantation.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/check_tile_for_incantation.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/player_actions.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
