/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_remaining_slots
*/

#include <string.h>
#include "server_implementation.h"

int get_remaining_slots(data_t *data, char *team_name)
{
    int curr_team_size = 0;

    for (unsigned int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->player && data->clients[i]->player->team_name &&
            !strcmp(data->clients[i]->player->team_name, team_name)) {
            curr_team_size++;
        }
    }
    return data->cli_per_team - curr_team_size;
}
