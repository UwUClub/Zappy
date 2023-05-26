target_sources(zappy_gui PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientApi.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ParserData.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp"
        )

target_include_directories(zappy_gui PRIVATE "../include")
