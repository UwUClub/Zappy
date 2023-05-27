/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** team_parser
*/

#include <string.h>
#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

static int append_to_team(data_t *data, char *team_name)
{
    int remaining_slots = get_remaining_slots(data, team_name);
    char *str_remaining_slots = NULL;
    char *world_dimensions = NULL;

    if (remaining_slots <= 0) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 84;
    }
    data->clients[data->curr_cli_index]->team_name = strdup(team_name);
    str_remaining_slots = inttos(remaining_slots - 1);
    str_remaining_slots = concat_str(str_remaining_slots, "\n");
    world_dimensions = get_world_dimensions(data);
    send_to_client(data->clients, data->curr_cli_index, str_remaining_slots);
    send_to_client(data->clients, data->curr_cli_index, world_dimensions);
    free(str_remaining_slots);
    free(world_dimensions);
    return 0;
}

static int append_to_gui(data_t *data)
{
    data->clients[data->curr_cli_index]->team_name = strdup("GRAPHIC");
    return msz(data, NULL);
}

int parse_team_name(data_t *data)
{
    if (!strcmp("GRAPHIC", data->clients[data->curr_cli_index]->input)) {
        return append_to_gui(data);
    }
    for (int i = 0; data->team_names[i]; i++) {
        if (!strcmp(data->team_names[i],
            data->clients[data->curr_cli_index]->input)) {
            return append_to_team(data, data->team_names[i]);
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return 0;
}
