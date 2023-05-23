/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** single_client_lifecycle
*/

#include "server_core.h"

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->username = NULL;
    (*client)->uuid = NULL;
    (*client)->input = NULL;
    (*client)->output = strdup("");
    (*client)->team_uuid = NULL;
    (*client)->channel_uuid = NULL;
    (*client)->thread_uuid = NULL;
}

void close_single_client(client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    if (client->username != NULL)
        free(client->username);
    if (client->uuid != NULL)
        free(client->uuid);
    if (client->input != NULL)
        free(client->input);
    if (client->output != NULL)
        free(client->output);
    if (client->team_uuid != NULL)
        free(client->team_uuid);
    if (client->channel_uuid != NULL)
        free(client->channel_uuid);
    if (client->thread_uuid != NULL)
        free(client->thread_uuid);
}
