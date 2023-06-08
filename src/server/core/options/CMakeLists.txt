set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/parse_options.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/option_setters.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/map_setters.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/print_help.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
