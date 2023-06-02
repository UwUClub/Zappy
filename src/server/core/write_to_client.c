/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** write_to_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "utils.h"

void send_to_client(client_t **clients, const int id, const char *msg)
{
    if (clients[id] && clients[id]->fd != -1) {
        clients[id]->output = concat_str(clients[id]->output, msg);
    }
}

void send_to_everyone(client_t **clients, const char *msg)
{
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd != -1) {
            clients[i]->output = concat_str(clients[i]->output, msg);
        }
    }
}

void write_to_selected_client(client_t **client)
{
    dprintf((*client)->fd, "%s", (*client)->output);
    if (!strcmp((*client)->output, "dead\n")) {
        close_single_client(*client);
        init_single_client(client);
    }
    free((*client)->output);
    (*client)->output = strdup("");
}
