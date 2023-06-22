/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pin
*/

#include "implementation.h"
#include "utils.h"
#include "ranges.h"

static char *get_pin_msg(player_t *player)
{
    char *msg = NULL;
    char *tmp = NULL;

    asprintf(&msg, "pin %d %d %d", player->id, player->pos->x, player->pos->y);
    for (int i = 0; i < TILE_SIZE; i++) {
        asprintf(&tmp, " %d", player->inventory[i]);
        msg = concat_str(msg, tmp);
        free(tmp);
    }
    msg = concat_str(msg, "\n");
    return msg;
}

void send_pin_to_all_gui(data_t *data, player_t *player)
{
    char *msg = NULL;

    msg = get_pin_msg(player);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

void send_pin_to_current_cli(data_t *data, player_t *player)
{
    char *msg = NULL;

    msg = get_pin_msg(player);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
}

int do_pin(data_t *data, char **args)
{
    player_t *player = NULL;
    char *msg = NULL;

    if (!args || word_array_len(args) != 1 || !is_int(args[0]))
        return ERROR_STATUS;
    player = get_player_by_id(data->clients, atoi(args[0]));
    if (!player)
        return ERROR_STATUS;
    msg = get_pin_msg(player);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return SUCCESS_STATUS;
}
