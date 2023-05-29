/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** single_client_lifecycle
*/

#include <unistd.h>
#include "server_core.h"

static void init_inventory(client_t **client)
{
    (*client)->inventory = malloc(sizeof(item_packet_t));
    (*client)->inventory->food = 10;
    (*client)->inventory->linemate = 0;
    (*client)->inventory->deraumere = 0;
    (*client)->inventory->sibur = 0;
    (*client)->inventory->mendiane = 0;
    (*client)->inventory->phiras = 0;
    (*client)->inventory->thystame = 0;
}

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->pos_x = -1;
    (*client)->pos_y = -1;
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
    if (client->inventory != NULL)
        free(client->inventory);
    if (client->team_name != NULL)
        free(client->team_name);
    if (client->input != NULL)
        free(client->input);
    if (client->output != NULL)
        free(client->output);
}
