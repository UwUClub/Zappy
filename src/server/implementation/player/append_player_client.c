/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** append_player_client
*/

#include <string.h>
#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"
#include "player_cmd.h"

int append_player_client(data_t *data, char *team_name)
{
    int remaining_slots = get_remaining_slots(data, team_name);
    char *str_remaining_slots = NULL;
    char *world_dimensions = NULL;

    if (remaining_slots <= 0) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 84;
    }
    init_player(&(data->clients[data->curr_cli_index]), team_name, data->map);
    str_remaining_slots = int_to_s(remaining_slots - 1);
    str_remaining_slots = concat_str(str_remaining_slots, "\n");
    world_dimensions = get_world_dimensions(data);
    send_to_client(data->clients, data->curr_cli_index, str_remaining_slots);
    send_to_client(data->clients, data->curr_cli_index, world_dimensions);
    free(str_remaining_slots);
    free(world_dimensions);
    return 0;
}
