/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pin
*/

#define _GNU_SOURCE
#include "implementation.h"
#include "utils.h"
#include "ranges.h"

int do_pin(data_t *data, char **args)
{
    player_t *player = NULL;
    char *msg = NULL;
    char *tmp = NULL;

    if (!args || word_array_len(args) != 1 || !is_int(args[0]))
        return ERROR_STATUS;
    player = get_player_by_id(data, atoi(args[0]));
    if (!player)
        return ERROR_STATUS;
    asprintf(&msg, "pin %s %d %d", args[0], player->pos->x, player->pos->y);
    for (int i = 0; i < TILE_SIZE; i++) {
        asprintf(&tmp, " %d", player->inventory[i]);
        msg = concat_str(msg, tmp);
        free(tmp);
    }
    msg = concat_str(msg, "\n");
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return SUCCESS_STATUS;
}
