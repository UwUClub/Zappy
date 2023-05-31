/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** left
*/

#include <stdio.h>
#include "server_implementation.h"

int move_left(data_t *data, char **args)
{
    if (args != NULL)
        return 1;
    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        data->clients[data->curr_cli_index]->orientation = WEST;
    if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        data->clients[data->curr_cli_index]->orientation = EAST;
    if (data->clients[data->curr_cli_index]->orientation == EAST)
        data->clients[data->curr_cli_index]->orientation = NORTH;
    if (data->clients[data->curr_cli_index]->orientation == WEST)
        data->clients[data->curr_cli_index]->orientation = SOUTH;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}
