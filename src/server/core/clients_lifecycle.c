/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** clients_lifecycle
*/

#include "server_core.h"

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
