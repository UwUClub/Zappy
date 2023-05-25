include_directories(cli)

add_executable(zappy_gui
        main.cpp
        cli/ClientApi.hpp
        cli/ClientApi.cpp
        cli/ParserData.hpp
        cli/ParserData.cpp
        cli/ServerData.hpp
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_gui
  PRIVATE myproject::myproject_options
        myproject::myproject_warnings
)

set_target_properties(zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
