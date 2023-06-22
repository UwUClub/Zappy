/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** write_to_client
*/

#include "core.h"
#include "utils.h"

void send_to_all_gui(client_t **clients, const char *msg)
{
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->fd != -1 && clients[i]->is_registered
            && clients[i]->player == NULL) {
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

int write_to_selected_client(data_t *data, client_t **client)
{
    dprintf((*client)->fd, "%s", (*client)->output);
    if (!strcmp((*client)->output, "dead\n")) {
        handle_client_quit(data);
        return 1;
    }
    free((*client)->output);
    (*client)->output = strdup("");
    return SUCCESS_STATUS;
}
