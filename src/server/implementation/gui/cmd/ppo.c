/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** ppo
*/

#define _GNU_SOURCE
#include "implementation.h"
#include "utils.h"

static char *get_ppo_msg(player_t *player)
{
    char *msg = NULL;

    asprintf(&msg, "ppo %d %d %d %d\n", player->id, player->pos->x,
        player->pos->y, player->orientation);
    return msg;
}

void send_ppo_to_all_gui(data_t *data, player_t *player)
{
    char *msg = NULL;

    msg = get_ppo_msg(player);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

int do_ppo(data_t *data, char **args)
{
    player_t *player = NULL;
    char *msg = NULL;

    if (!args || word_array_len(args) != 1 || !is_int(args[0]))
        return ERROR_STATUS;
    player = get_player_by_id(data->clients, atoi(args[0]));
    if (!player)
        return ERROR_STATUS;
    msg = get_ppo_msg(player);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return SUCCESS_STATUS;
}
