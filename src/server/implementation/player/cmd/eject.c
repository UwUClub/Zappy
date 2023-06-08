/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** eject
*/

#include "implementation.h"
#include "player_cmd.h"

static void eject_player(data_t *data, int index)
{
    player_t *player = data->clients[index]->player;
    char *msg = NULL;

    if (player->pos->x != data->clients[data->curr_cli_index]->player->pos->x
    || player->pos->y != data->clients[data->curr_cli_index]->player->pos->y)
        return;
    switch (data->clients[data->curr_cli_index]->player->orientation) {
        case NORTH:
            player->pos->y -= 1;
        case SOUTH:
            player->pos->y += 1;
        case EAST:
            player->pos->x += 1;
        case WEST:
            player->pos->x -= 1;
    }
    asprintf(&msg, "eject\n");
    send_to_client(data->clients, index, msg);
    free(msg);
}

static int eject_cmd(data_t *data, __attribute__((unused)) char **args)
{
    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data, i) && i != data->curr_cli_index) {
            eject_player(data, i);
        }
    }
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
