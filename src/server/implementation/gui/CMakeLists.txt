set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/append_gui_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/gui_cmd_executor.c"
        )

add_subdirectory(cmd)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cmd")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
