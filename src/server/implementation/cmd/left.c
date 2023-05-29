/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** left
*/

#include <stdio.h>
#include "server_implementation.h"

int left(data_t *data, __attribute__ ((unused)) char **args)
{
    char *myMsg = strdup("ok");

    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        data->clients[data->curr_cli_index]->orientation = WEST;
    if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        data->clients[data->curr_cli_index]->orientation = EAST;
    if (data->clients[data->curr_cli_index]->orientation == EAST)
        data->clients[data->curr_cli_index]->orientation = NORTH;
    if (data->clients[data->curr_cli_index]->orientation == WEST)
        data->clients[data->curr_cli_index]->orientation = SOUTH;
    send_to_client(data->clients, data->curr_cli_index, myMsg);
    free(myMsg);
    return 0;
}

