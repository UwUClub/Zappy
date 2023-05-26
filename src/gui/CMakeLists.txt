include_directories(cli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -ldl -lpthread -lX11 -lXrandr -lXi")

add_executable(zappy_gui
        main.cpp
        App.cpp
        cli/ClientApi.hpp
        cli/ClientApi.cpp
        cli/ParserData.hpp
        cli/ParserData.cpp
        cli/ServerData.hpp
        cli/GetOpt.cpp
        cli/GetOpt.hpp
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(zappy_gui
    PRIVATE myproject::myproject_options
        myproject::myproject_warnings
        Vulkan::Vulkan
)

set_target_properties(zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
