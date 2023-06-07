/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** check_player_in_tile
*/

#include <stdio.h>
#include "implementation.h"

client_t **check_player_on_tile(data_t *data, const int x, const int y)
{
    client_t **clients = NULL;
    int index = 0;

    for (unsigned int i = 0; data->clients[i] != NULL; i++) {
        if (data->clients[i]->player->pos->x == x
            && data->clients[i]->player->pos->y == y) {
            clients = realloc(clients, sizeof(client_t *) * (index + 2));
            clients[index + 1] = NULL;
            clients[index] = data->clients[i];
            index++;
        }
    }
    return clients;
}
