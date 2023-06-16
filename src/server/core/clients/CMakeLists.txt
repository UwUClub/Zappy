set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/clients_lifecycle.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_client_quit.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_clients.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/read_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/welcome_single_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/write_to_client.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
