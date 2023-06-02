/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_next_timeout
*/

#include "core.h"
#include <sys/time.h>

struct timeval *get_next_timeout(data_t *data)
{
    struct timeval *timeout = NULL;
    unsigned long long smallest_remaining_ms = -1;

    for (int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->fd >= 0 && data->clients[i]->player &&
            data->clients[i]->player->pending_cmd_queue[0] &&
            (smallest_remaining_ms == -1 ||
            data->clients[i]->player->pending_cmd_queue[0]->remaining_ms <
            smallest_remaining_ms)) {
                smallest_remaining_ms =
                data->clients[i]->player->pending_cmd_queue[0]->remaining_ms;
        }
    }
    if (smallest_remaining_ms == -1)
        return NULL;
    timeout = malloc(sizeof(struct timeval));
    timeout->tv_sec = smallest_remaining_ms / MS_FACTOR;
    timeout->tv_usec = (smallest_remaining_ms % MS_FACTOR) * MS_FACTOR;
    return timeout;
}
