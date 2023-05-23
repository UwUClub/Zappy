add_executable(zappy_gui
        main.cpp
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_gui
  PRIVATE myproject::myproject_options
        myproject::myproject_warnings
)
