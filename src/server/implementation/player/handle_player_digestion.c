/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_player_digestion
*/

#include "implementation.h"
#include "resources.h"
#include "ranges.h"

static void eat_food(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    player->inventory[FOOD]--;
    player->remaining_digestion_ms = (DIGESTION_TIME * MS_FACTOR) / data->freq;
}

void handle_player_digestion(data_t *data, unsigned long long elapsed_time_ms)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    if (elapsed_time_ms >= player->remaining_digestion_ms) {
        if (player->inventory[FOOD] > 0)
            eat_food(data);
        else
            kill_player(data);
    } else {
        player->remaining_digestion_ms -= elapsed_time_ms;
    }
}
