/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** left
*/

#include <stdio.h>
#include "server_implementation.h"

int left(__attribute__ ((unused)) data_t *data,
    __attribute__ ((unused)) char **args)
{
    char *msg = strdup("ok");

    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        data->clients[data->curr_cli_index]->orientation = WEST;
    else if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        data->clients[data->curr_cli_index]->orientation = EAST;
    else if (data->clients[data->curr_cli_index]->orientation == EAST)
        data->clients[data->curr_cli_index]->orientation = NORTH;
    else if (data->clients[data->curr_cli_index]->orientation == WEST)
        data->clients[data->curr_cli_index]->orientation = SOUTH;
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}

