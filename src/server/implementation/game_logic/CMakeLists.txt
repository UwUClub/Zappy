set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/detect_win.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_next_timeout.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/spawn_resources.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
