set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

include_directories(core)
include_directories(implementation)
include_directories(utils)
include_directories(include)

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/handle_clients.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/launch_server.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/read_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/single_client_lifecycle.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/welcome_single_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/write_to_client.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/implementation/cmd_parser.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/implementation/team_parser.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/implementation/get_remaining_slots.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/implementation/cmd/msz.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/implementation/cmd/forward.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/concat_str.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/free_word_array.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/get_sockaddr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/inttos.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/is_int.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/revstr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/str_to_word_array.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/word_array_len.c"
        )

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
