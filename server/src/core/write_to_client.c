/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** write_to_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server_core.h"
#include "utils.h"

void add_output(client_t **client, const char *msg)
{
    (*client)->output = concat_str((*client)->output, msg);
}

void broadcast_uuid(client_t **clients, const char *uuid, const char *msg)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (clients[i]->fd != -1 && !strcmp(clients[i]->uuid, uuid)) {
            clients[i]->output = concat_str(clients[i]->output, msg);
        }
    }
}

void broadcast_everyone(client_t **clients, const char *msg)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (clients[i]->fd != -1 && clients[i]->uuid != NULL) {
            clients[i]->output = concat_str(clients[i]->output, msg);
        }
    }
}

void write_to_selected_client(client_t **client)
{
    dprintf((*client)->fd, "%s", (*client)->output);
    free((*client)->output);
    (*client)->output = strdup("");
}
