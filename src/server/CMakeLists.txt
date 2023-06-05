set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

include_directories(core)
include_directories(implementation)
include_directories(utils)
include_directories(include)
include_directories(include/implementation)

add_executable(zappy_server
        main.c
        core/options/parse_options.c
        core/options/option_setters.c
        core/options/map_setters.c
        core/options/print_help.c
        core/handle_clients.c
        core/launch_server.c
        core/server_data.c
        core/detect_win.c
        core/read_client.c
        core/clients_lifecycle.c
        core/welcome_single_client.c
        core/write_to_client.c
        core/spawn_resources.c
        core/get_next_timeout.c
        core/handle_client_quit.c
        implementation/input_parser.c
        implementation/is_player.c
        implementation/event/seg.c
        implementation/get_remaining_slots.c
        implementation/check_player_on_tile.c
        implementation/gui/append_gui_client.c
        implementation/gui/gui_cmd_executor.c
        implementation/gui/cmd/msz.c
        implementation/gui/cmd/bct.c
        implementation/gui/cmd/tna.c
        implementation/gui/cmd/sgt.c
        implementation/gui/cmd/pin.c
        implementation/player/append_player_client.c
        implementation/player/player_cmd_scheduler.c
        implementation/player/handle_pending_cmd.c
        implementation/player/handle_player_digestion.c
        implementation/player/kill_player.c
        implementation/player/get_player_by_id.c
        implementation/player/cmd/forward.c
        implementation/player/cmd/right.c
        implementation/player/cmd/left.c
        implementation/player/cmd/take.c
        implementation/player/cmd/set.c
        implementation/player/cmd/inventory.c
        implementation/player/cmd/connect_nbr.c
        implementation/player/cmd/look.c
        utils/concat_str.c
        utils/free_word_array.c
        utils/get_sockaddr.c
        utils/int_to_s.c
        utils/is_int.c
        utils/revstr.c
        utils/str_to_word_array.c
        utils/word_array_len.c
        utils/get_ms_since_epoch.c
        utils/calc_outbound.c
        include/core.h
        include/utils.h
        include/resources.h
        include/ranges.h
        include/implementation/implementation.h
        include/implementation/gui_cmd.h
        include/implementation/player_cmd.h
        )


target_include_directories(zappy_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../../"
)
