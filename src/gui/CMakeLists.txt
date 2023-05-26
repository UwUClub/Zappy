include_directories(cli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lvulkan -lglfw -ldl -lpthread -lX11 -lXrandr -lXi")

target_sources(zappy_gui PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/App.cpp"
        )

add_subdirectory(cli)

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cli")
