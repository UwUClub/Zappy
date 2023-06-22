/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_player_by_id
*/

#include "core.h"

player_t *get_player_by_id(client_t **clients, const unsigned int id)
{
    player_t *player = NULL;

    for (int i = 0; clients[i]; i++) {
        if (clients[i]->is_registered &&
        clients[i]->player && clients[i]->player->id == id) {
            player = clients[i]->player;
            break;
        }
    }
    return player;
}
