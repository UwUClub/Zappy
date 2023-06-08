/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** single_client_lifecycle
*/

#include "core.h"

static void init_inventory(client_t **client)
{
    (*client)->inventory[0] = 0;
    (*client)->inventory[1] = 0;
    (*client)->inventory[2] = 0;
    (*client)->inventory[3] = 0;
    (*client)->inventory[4] = 0;
    (*client)->inventory[5] = 0;
    (*client)->inventory[6] = 0;
}

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->pos = NULL;
    (*client)->orientation = UNKNOWN;
    (*client)->level = 0;
    init_inventory(client);
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
