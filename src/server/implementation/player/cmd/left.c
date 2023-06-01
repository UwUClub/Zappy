/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** left
*/

#include <stdio.h>
#include "implementation.h"

int move_left(data_t *data, char **args)
{
    if (args != NULL)
        return 1;
    if (data->clients[data->curr_cli_index]->player->orientation == NORTH)
        data->clients[data->curr_cli_index]->player->orientation = WEST;
    if (data->clients[data->curr_cli_index]->player->orientation == SOUTH)
        data->clients[data->curr_cli_index]->player->orientation = EAST;
    if (data->clients[data->curr_cli_index]->player->orientation == EAST)
        data->clients[data->curr_cli_index]->player->orientation = NORTH;
    if (data->clients[data->curr_cli_index]->player->orientation == WEST)
        data->clients[data->curr_cli_index]->player->orientation = SOUTH;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}
