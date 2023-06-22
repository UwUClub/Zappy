/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pnw
*/

#include "core.h"

static char *get_pnw_msg(player_t *player)
{
    char *msg = NULL;

    asprintf(&msg, "pnw %d %d %d %d %d %s\n", player->id, player->pos->x,
        player->pos->y, player->orientation, player->level, player->team_name);
    return msg;
}

void send_pnw_to_current_cli(data_t *data, player_t *player)
{
    char *msg = NULL;

    msg = get_pnw_msg(player);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
}

void send_pnw_to_all_gui(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;
    char *msg = NULL;

    msg = get_pnw_msg(player);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
