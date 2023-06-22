/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** is_player
*/

#include "core.h"

int is_player(client_t **clients, const int i)
{
    if (clients[i]->fd != -1 && clients[i]->is_registered == 1 &&
        clients[i]->player != NULL &&
        clients[i]->player->team_name != NULL) {
        return 1;
    }
    return SUCCESS_STATUS;
}
