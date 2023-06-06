set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/concat_str.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/free_word_array.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_sockaddr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/int_to_s.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_int.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/revstr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/str_to_word_array.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/word_array_len.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_ms_since_epoch.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/calc_outbound.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/concat_word_array.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_ip.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
