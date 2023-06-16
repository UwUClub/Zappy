/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_next_timeout
*/

#include "core.h"
#include <sys/time.h>

static void update_smallest_remaining_ms_from_player(player_t *player,
    unsigned long long *smallest_remaining_ms)
{
    if (player->remaining_digestion_ms < *smallest_remaining_ms) {
        *smallest_remaining_ms = player->remaining_digestion_ms;
    }
    if (player->pending_cmd_queue[0] && (*smallest_remaining_ms == -1 ||
    player->pending_cmd_queue[0]->remaining_ms < *smallest_remaining_ms)) {
        *smallest_remaining_ms = player->pending_cmd_queue[0]->remaining_ms;
    }
}

static void check_players_remaining_ms(client_t **clients,
    unsigned long long *smallest_remaining_ms)
{
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd >= 0 && clients[i]->player) {
            update_smallest_remaining_ms_from_player(clients[i]->player,
            smallest_remaining_ms);
        }
    }
}

static void update_smallest_remaining_ms_from_egg(egg_t *egg,
    unsigned long long *smallest_remaining_ms)
{
    if (egg->remaining_digestion_ms < *smallest_remaining_ms) {
        *smallest_remaining_ms = egg->remaining_digestion_ms;
    }
}

static void check_eggs_remaining_ms(team_t **teams,
    unsigned long long *smallest_remaining_ms)
{
    for (int i = 0; teams[i]; i++) {
        for (int j = 0; teams[i]->eggs[j]; j++) {
            update_smallest_remaining_ms_from_egg(teams[i]->eggs[j],
            smallest_remaining_ms);
        }
    }
}

struct timeval *get_next_timeout(data_t *data)
{
    struct timeval *timeout = NULL;
    unsigned long long smallest_remaining_ms = data->remaining_rsrc_spawn_ms;

    check_players_remaining_ms(data->clients, &smallest_remaining_ms);
    check_eggs_remaining_ms(data->teams, &smallest_remaining_ms);
    if (smallest_remaining_ms == -1)
        return NULL;
    timeout = malloc(sizeof(struct timeval));
    timeout->tv_sec = smallest_remaining_ms / MS_FACTOR;
    timeout->tv_usec = (smallest_remaining_ms % MS_FACTOR) * MS_FACTOR;
    return timeout;
}
