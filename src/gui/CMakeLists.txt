set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi")

add_executable(zappy_gui
        main.cpp
        App.cpp
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
