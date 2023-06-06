set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_clients.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/launch_server.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/server_data.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/detect_win.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/read_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/clients_lifecycle.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/welcome_single_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/write_to_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/spawn_resources.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_next_timeout.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/handle_client_quit.c"
        )

add_subdirectory(options)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/options")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
