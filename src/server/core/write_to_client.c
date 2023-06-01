/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** write_to_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server_core.h"
#include "utils.h"

void send_to_all_gui(client_t **clients, const char *msg)
{
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->fd != -1
            && clients[i]->team_name != NULL &&
            strcmp(clients[i]->team_name, "GRAPHIC") == 0) {
                send_to_client(clients, i, msg);
        }
    }
}

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
    free((*client)->output);
    (*client)->output = strdup("");
}
