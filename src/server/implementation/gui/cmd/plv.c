/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** plv
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "implementation.h"
#include "utils.h"

void send_plv_to_all_gui(data_t *data, player_t *player)
{
    char *msg = NULL;

    asprintf(&msg, "plv %d %d\n", player->id, player->level);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

int do_plv(data_t *data, char **args)
{
    player_t *player = NULL;
    char *msg = NULL;

    if (!args || word_array_len(args) != 1 || !is_int(args[0]))
        return 1;
    player = get_player_by_id(data, atoi(args[0]));
    if (!player)
        return 1;
    asprintf(&msg, "plv %s %d\n", args[0], player->level);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}
