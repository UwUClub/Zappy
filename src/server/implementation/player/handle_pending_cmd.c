/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_pending_cmd
*/

#include <time.h>
#include "implementation.h"
#include "utils.h"

static void shift_pending_cmd(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    free_word_array(player->pending_cmd_queue[0]->args);
    free(player->pending_cmd_queue[0]);
    for (int j = 0; j < MAX_PENDING_CMD - 1; j++) {
        player->pending_cmd_queue[j] =
            player->pending_cmd_queue[j + 1];
    }
    player->pending_cmd_queue[MAX_PENDING_CMD - 1] = NULL;
}

static void treat_pending_cmd(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    if (player->pending_cmd_queue[0]->remaining_ms <= 0) {
        player->pending_cmd_queue[0]->func(data,
            player->pending_cmd_queue[0]->args);
        shift_pending_cmd(data);
    }
}

void handle_pending_cmd(data_t *data)
{
    unsigned long long elapsed_time_ms = 0;
    player_t *player = data->clients[data->curr_cli_index]->player;

    elapsed_time_ms = get_ms_since_epoch() - data->last_select_ms;
    if (elapsed_time_ms >= player->pending_cmd_queue[0]->remaining_ms)
        player->pending_cmd_queue[0]->remaining_ms = 0;
    else
        player->pending_cmd_queue[0]->remaining_ms -= elapsed_time_ms;
    treat_pending_cmd(data);
}
