/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** send_pnw
*/

#include "core.h"

void do_pnw(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;
    char *msg = NULL;

    asprintf(&msg, "pnw %d %d %d %d %d %s\n", data->curr_cli_index,
        player->pos->x, player->pos->y, player->orientation, player->level,
        player->team_name);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
