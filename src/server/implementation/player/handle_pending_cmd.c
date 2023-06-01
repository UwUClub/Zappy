/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_pending_cmd
*/

#include <time.h>
#include "implementation.h"

static void shift_pending_cmd(data_t *data, const int id)
{
    free(data->clients[id]->player->pending_cmd_queue[0]);
    for (int j = 0; j < MAX_PENDING_CMD - 1; j++) {
        data->clients[id]->player->pending_cmd_queue[j] =
            data->clients[id]->player->pending_cmd_queue[j + 1];
    }
    data->clients[id]->player->pending_cmd_queue[MAX_PENDING_CMD - 1] = NULL;
}

static void treat_pending_cmd(data_t *data, const int id)
{
    if (data->clients[id]->player->pending_cmd_queue[0]->remaining <= 0) {
        data->clients[id]->player->pending_cmd_queue[0]->func(data,
            data->clients[id]->player->pending_cmd_queue[0]->args);
        shift_pending_cmd(data, id);
    }
}

void handle_pending_cmd(data_t *data)
{
    time_t elapsed_time = 0;

    elapsed_time = time(NULL) - data->last_select;
    for (int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->fd >= 0 && data->clients[i]->player &&
            data->clients[i]->player->pending_cmd_queue[0]) {
            data->clients[i]->player->pending_cmd_queue[0]->remaining -=
                elapsed_time;
            treat_pending_cmd(data, i);
        }
    }
}
