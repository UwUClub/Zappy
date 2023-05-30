/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** forward
*/

#include <stdio.h>
#include "server_implementation.h"

int forward(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        data->clients[data->curr_cli_index]->pos_y -= 1;
    if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        data->clients[data->curr_cli_index]->pos_y += 1;
    if (data->clients[data->curr_cli_index]->orientation == EAST)
        data->clients[data->curr_cli_index]->pos_x += 1;
    if (data->clients[data->curr_cli_index]->orientation == WEST)
        data->clients[data->curr_cli_index]->pos_x -= 1;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}
