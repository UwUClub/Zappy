/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** kill_player
*/

#include "core.h"

void kill_player(data_t *data)
{
    send_to_client(data->clients, data->curr_cli_index, "dead\n");
}
