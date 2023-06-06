set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/broadcast.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_tile_from_source.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
