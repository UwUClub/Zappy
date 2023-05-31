/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** right
*/

#include <stdio.h>
#include "server_implementation.h"

int right(data_t *data, char **args)
{
    if (args != NULL)
        return 1;
    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        data->clients[data->curr_cli_index]->orientation = EAST;
    if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        data->clients[data->curr_cli_index]->orientation = WEST;
    if (data->clients[data->curr_cli_index]->orientation == EAST)
        data->clients[data->curr_cli_index]->orientation = SOUTH;
    if (data->clients[data->curr_cli_index]->orientation == WEST)
        data->clients[data->curr_cli_index]->orientation = NORTH;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}
