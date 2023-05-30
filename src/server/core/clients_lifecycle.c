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

client_t **init_clients(const unsigned int max_connections)
{
    client_t **clients = NULL;
    unsigned int i = 0;

    clients = malloc(sizeof(client_t *) * (max_connections + 1));
    for (i = 0; i < max_connections; i++) {
        clients[i] = malloc(sizeof(client_t));
        init_single_client(&clients[i]);
    }
    clients[i] = NULL;
    return clients;
}

void close_clients(client_t **clients)
{
    for (int i = 0; clients[i]; i++) {
        close_single_client(clients[i]);
        free(clients[i]);
    }
    free(clients);
}
