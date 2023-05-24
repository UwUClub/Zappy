/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_remaining_slots
*/

#include <stdio.h>
#include <string.h>
#include "server_implementation.h"
#include "utils.h"

char *get_remaining_slots(data_t *data, char *team_name)
{
    int curr_team_size = 0;
    char *result = strdup("");

    for (int i = 0; data->clients[i]; i++)
        if (data->clients[i]->team_name && !strcmp(data->clients[i]->team_name, team_name))
            curr_team_size++;
    result = concat_str(result, inttos(data->cli_per_team - curr_team_size));
    result = concat_str(result, "\n");
    return result;
}
