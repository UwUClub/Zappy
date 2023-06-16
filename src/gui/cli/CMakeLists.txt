target_sources(zappy_gui PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientApi.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientApi+Listener.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ItemPacket.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ParserData.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/PlayerData.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/EggData.cpp"
        )

target_include_directories(zappy_gui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "../${CMAKE_CURRENT_SOURCE_DIR}")
