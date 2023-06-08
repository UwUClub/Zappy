/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** eject
*/

#include "implementation.h"
#include "player_cmd.h"

static void eject_player(data_t *data, const int player_index, player_t *kicker)
{
    player_t *player = data->clients[player_index]->player;

    if (player->pos->x != kicker->pos->x || player->pos->y != kicker->pos->y)
        return;
    switch (kicker->orientation) {
        case NORTH:
            data->clients[player_index]->player->pos->y -= 1;
            break;
        case SOUTH:
            data->clients[player_index]->player->pos->y += 1;
            break;
        case EAST:
            data->clients[player_index]->player->pos->x += 1;
            break;
        case WEST:
            data->clients[player_index]->player->pos->x -= 1;
            break;
    }
    normalize_pos(data->clients[player_index]->player->pos, data->map->width,
        data->map->height);
    if (player->pending_cmd_queue[0] != NULL) {
        shift_pending_cmd(data, player_index);
        send_to_client(data->clients, player_index, "ko\n");
    }
    send_to_client(data->clients, player_index, "eject\n");
    // do pex
}

static void hatch_eggs_at(data_t *data, const int x, const int y)
{
}

static int eject_cmd(data_t *data, __attribute__((unused)) char **args)
{
    player_t *kicker = data->clients[data->curr_cli_index]->player;

    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data, i) && i != data->curr_cli_index) {
            eject_player(data, i, kicker);
        }
    }
    hatch_eggs_at(data, kicker->pos->x, kicker->pos->y);
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}

int schedule_eject(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    append_scheduler_to_queue(data, &eject_cmd, args, EJECT_DELAY);
    return 0;
}
