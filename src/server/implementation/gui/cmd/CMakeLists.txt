set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

target_sources(zappy_server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/msz.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/bct.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tna.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/sgt.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/sst.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/pin.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/plv.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ppo.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/seg.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/enw.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/pfk.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/pnw.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ebo.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/edi.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/pdr.c"
        )

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
