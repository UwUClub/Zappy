set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/init_server_data.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/init_map.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/init_teams.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/free_server_data.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
