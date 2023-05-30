/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** single_client_lifecycle
*/

#include <unistd.h>
#include "server_core.h"

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->pos_x = -1;
    (*client)->pos_y = -1;
    (*client)->orientation = UNKNOWN;
    (*client)->level = 0;
    for (int i = 0; i < TILE_SIZE; i++)
        (*client)->inventory[i] = 0;
    (*client)->team_name = NULL;
    (*client)->input = NULL;
    (*client)->output = strdup("");
}

void close_single_client(client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    if (client->team_name != NULL)
        free(client->team_name);
    if (client->input != NULL)
        free(client->input);
    if (client->output != NULL)
        free(client->output);
}
