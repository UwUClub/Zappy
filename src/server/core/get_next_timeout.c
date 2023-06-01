/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_next_timeout
*/

#include "core.h"

struct timeval *get_next_timeout(data_t *data)
{
    struct timeval *timeout = NULL;
    long smallest_remaining = -1;

    for (int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->fd >= 0 && data->clients[i]->player &&
            data->clients[i]->player->pending_cmd_queue[0] &&
            (smallest_remaining == -1 ||
            data->clients[i]->player->pending_cmd_queue[0]->remaining <
                smallest_remaining)) {
                smallest_remaining =
                    data->clients[i]->player->pending_cmd_queue[0]->remaining;
        }
    }
    if (smallest_remaining == -1)
        return NULL;
    timeout = malloc(sizeof(struct timeval));
    timeout->tv_sec = smallest_remaining;
    timeout->tv_usec = 0;
    return timeout;
}
