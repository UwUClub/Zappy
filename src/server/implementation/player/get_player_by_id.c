/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_player_by_id
*/

#include "core.h"

player_t *get_player_by_id(data_t *data, const unsigned int id)
{
    player_t *player = NULL;

    for (int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->is_registered &&
        data->clients[i]->player && data->clients[i]->player->id == id) {
            player = data->clients[i]->player;
        }
        if (i == id) {
            break;
        }
    }
    return player;
}
