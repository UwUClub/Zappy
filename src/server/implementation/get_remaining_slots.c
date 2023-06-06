/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_remaining_slots
*/

#include <string.h>
#include "implementation.h"

int get_remaining_slots(data_t *data, char *team_name)
{
    int curr_team_size = 0;

    for (unsigned int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->player && data->clients[i]->player->team_name &&
            !strcmp(data->clients[i]->player->team_name, team_name)) {
            curr_team_size++;
        }
    }
    for (unsigned int i = 0; data->teams[i]; i++) {
        if (!strcmp(data->teams[i]->name, team_name)) {
            return data->teams[i]->nb_cli - curr_team_size;
        }
    }
    return -1;
}
