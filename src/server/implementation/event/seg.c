/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** seg
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

static int seg(data_t *data, const char *team_name)
{
    char *msg = NULL;

    if (team_name == NULL)
        return 1;
    msg = strdup("seg ");
    msg = concat_str(msg, team_name);
    msg = concat_str(msg, "\n");
    send_to_all_gui(msg, data->clients);
    free(msg);
    return 0;
}

int end_of_game(data_t *data)
{
    client_t **clients = NULL;

    clients = data->clients;
    if (clients == NULL)
        return 1;
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->fd != -1 && clients[i]->is_registered == 1 && 
            clients[i]->player != NULL && clients[i]->player->team_name != NULL
            && clients[i]->player->level == 8) {
                seg(data, clients[i]->player->team_name);
        }
    }
}