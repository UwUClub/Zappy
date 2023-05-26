include_directories(cli)

if (NO_CONNECTION EQUAL 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -lX11 -lXrandr -lXi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -ldl -lpthread -lX11 -lXrandr -lXi")
endif()

add_executable(zappy_gui
        main.cpp
        App.cpp
        cli/ClientApi.hpp
        cli/ClientApi.cpp
        cli/ParserData.hpp
        cli/ParserData.cpp
        cli/ServerData.hpp
        cli/Player.cpp
        cli/Player.hpp
        )

add_subdirectory(cli)

target_link_libraries(zappy_gui
    PRIVATE myproject::myproject_options
        myproject::myproject_warnings
        Vulkan::Vulkan
        glfw
)

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cli")

set_target_properties(zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
