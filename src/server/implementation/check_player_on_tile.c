/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** check_player_in_tile
*/

#include <stdio.h>
#include "server_implementation.h"

client_t **check_player_on_tile(data_t *data, int x, int y)
{
    client_t **clients = NULL;
    int index = 0;

    for (unsigned int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->pos_x == x && data->clients[i]->pos_y == y) {
            clients = realloc(clients, sizeof(client_t *) * (index + 2));
            clients[index + 1] = NULL;
            clients[index] = data->clients[i];
            index++;
        }
    }
    return clients;
}
