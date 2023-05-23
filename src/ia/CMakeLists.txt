add_executable(zappy_ia
        main.c
        )

target_include_directories(zappy_ia PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_ia
  PRIVATE myproject::myproject_options
        myproject::myproject_warnings
)
