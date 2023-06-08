set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/forward.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/right.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/left.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/take.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/set.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/inventory.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/connect_nbr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/look.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/fork.c"
        )

add_subdirectory(broadcast)
add_subdirectory(incantation)

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/incantation")
target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/broadcast")


set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
