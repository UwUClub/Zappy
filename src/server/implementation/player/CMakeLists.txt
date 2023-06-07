set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/append_player_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/player_cmd_scheduler.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_pending_cmd.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_player_digestion.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/kill_player.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_player_by_id.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/team_getters.c"
        )

add_subdirectory(cmd)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cmd")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
