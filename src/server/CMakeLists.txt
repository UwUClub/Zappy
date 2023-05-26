set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

include_directories(core)
include_directories(implementation)
include_directories(utils)
include_directories(include)

add_executable(zappy_server
        main.c
        core/options/parse_options.c
        core/options/option_setters.c
        core/handle_clients.c
        core/launch_server.c
        core/read_client.c
        core/single_client_lifecycle.c
        core/welcome_single_client.c
        core/write_to_client.c
        implementation/cmd_parser.c
        implementation/team_parser.c
        implementation/get_remaining_slots.c
        implementation/cmd/msz.c
        implementation/cmd/forward.c
        utils/concat_str.c
        utils/free_word_array.c
        utils/get_sockaddr.c
        utils/inttos.c
        utils/is_int.c
        utils/revstr.c
        utils/str_to_word_array.c
        utils/word_array_len.c
        include/server_implementation.h
        include/server_core.h
        include/utils.h
        )

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_server
  PRIVATE myproject::myproject_options
        myproject::myproject_warnings
)

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
