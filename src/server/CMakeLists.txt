set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -std=gnu99")

add_executable(zappy_server
        main.c
)

add_subdirectory(core)
add_subdirectory(implementation)
add_subdirectory(utils)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/core")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/implementation")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/utils")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/core")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/implementation")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
