cmake_minimum_required(VERSION 3.13)  # CMake version check
set(PROJECT_NAME server)
project(${PROJECT_NAME})            # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++14 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

include_directories(src)
include_directories(src/core)
include_directories(src/implementation)
include_directories(src/utils)
include_directories(include)

set(SOURCE_FILES
    src/main.c
    src/core/handle_clients.c
    src/core/launch_server.c
    src/core/read_client.c
    src/core/single_client_lifecycle.c
    src/core/welcome_single_client.c
    src/core/write_to_client.c
    src/implementation/cmd_parser.c
    src/implementation/msz.c
    src/implementation/forward.c
    src/utils/concat_str.c
    src/utils/free_word_array.c
    src/utils/get_file_length.c
    src/utils/get_sockaddr.c
    src/utils/inttos.c
    src/utils/is_int.c
    src/utils/parse_quotes.c
    src/utils/revstr.c
    src/utils/rm_line_from_file.c
    src/utils/str_to_word_array.c
    src/utils/word_array_len.c
    include/server_implementation.h
    include/server_core.h
    include/utils.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    COMPILE_FLAGS ""
)
