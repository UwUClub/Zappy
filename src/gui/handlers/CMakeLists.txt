add_subdirectory(events)

target_sources(zappy_gui PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/AnimationHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MovementHandler.cpp"
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
