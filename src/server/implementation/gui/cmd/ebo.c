/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** ebo
*/

#include "core.h"

void send_ebo_to_all_gui(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;
    char *msg = NULL;

    asprintf(&msg, "ebo %d\n", player->id);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
