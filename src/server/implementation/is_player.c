/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** is_player
*/

#include "core.h"

int is_player(data_t *data, const int i)
{
    if (data->clients[i]->fd != -1 && data->clients[i]->is_registered == 1 &&
        data->clients[i]->player != NULL &&
        data->clients[i]->player->team_name != NULL) {
            return 1;
    }
    return 0;
}
