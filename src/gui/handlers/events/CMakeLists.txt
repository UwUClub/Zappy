target_sources(zappy_gui PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MouseHandler.cpp"
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
