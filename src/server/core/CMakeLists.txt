set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/launch_server.c"
        )

add_subdirectory(clients)
add_subdirectory(options)
add_subdirectory(server_data)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/clients")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/options")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/server_data")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
