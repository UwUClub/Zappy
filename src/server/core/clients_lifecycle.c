/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** clients_lifecycle
*/

#include <unistd.h>
#include "server_core.h"

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->is_registered = 0;
    (*client)->player = NULL;
    (*client)->input = NULL;
    (*client)->output = strdup("");
}

void init_player(client_t **client, const char *team_name,
    const int map_width, const int map_height)
{
    (*client)->player = malloc(sizeof(player_t));
    (*client)->player->pos_x = rand() % map_width;
    (*client)->player->pos_y = rand() % map_height;
    (*client)->player->orientation = NORTH;
    (*client)->player->level = 0;
    for (int i = 0; i < TILE_SIZE; i++) {
        (*client)->player->inventory[i] = 0;
    }
    (*client)->player->team_name = strdup(team_name);
}

void close_single_client(client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    if (client->player != NULL) {
        if (client->player->team_name != NULL)
            free(client->player->team_name);
        free(client->player);
    }
    if (client->input != NULL)
        free(client->input);
    if (client->output != NULL)
        free(client->output);
}

void close_clients(client_t **clients)
{
    for (int i = 0; clients[i]; i++) {
        close_single_client(clients[i]);
        free(clients[i]);
    }
    free(clients);
}
