/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** eject
*/

#include "implementation.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static void perform_ejection(orientation_t orientation, pos_t *player_pos)
{
    switch (orientation) {
        case NORTH:
            player_pos->y -= 1;
            break;
        case SOUTH:
            player_pos->y += 1;
            break;
        case EAST:
            player_pos->x += 1;
            break;
        case WEST:
            player_pos->x -= 1;
            break;
        default:
            break;
    }
}

static void eject_player(data_t *data, const int player_index, player_t *kicker)
{
    player_t *player = data->clients[player_index]->player;

    if (player->pos->x != kicker->pos->x || player->pos->y != kicker->pos->y)
        return;
    perform_ejection(kicker->orientation, player->pos);
    normalize_pos(data->clients[player_index]->player->pos, data->map->width,
        data->map->height);
    if (player->pending_cmd_queue[0] != NULL) {
        shift_pending_cmd(data, player_index);
        send_to_client(data->clients, player_index, "ko\n");
    }
    send_to_client(data->clients, player_index, "eject\n");
    do_pex(data, player->id);
}

static int eject_cmd(data_t *data, __attribute__((unused)) char **args)
{
    player_t *kicker = data->clients[data->curr_cli_index]->player;

    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data, i) && i != data->curr_cli_index) {
            eject_player(data, i, kicker);
        }
    }
    hatch_eggs_at_pos(data, kicker->pos);
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
