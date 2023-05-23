add_executable(zappy_server
        main.c
        )

target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_server
  PRIVATE myproject::myproject_options
        myproject::myproject_warnings
)
