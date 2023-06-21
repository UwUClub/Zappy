/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** take
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"
#include "resources.h"

static int is_resource_on_tile(data_t *data, const int resource, pos_t *pos)
{
    return data->map->tiles[pos->x][pos->y][resource] > 0;
}

static int take(data_t *data, char **args)
{
    pos_t *player_pos = data->clients[data->curr_cli_index]->player->pos;

    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && is_resource_on_tile(data, i, player_pos)) {
            data->clients[data->curr_cli_index]->player->inventory[i] += 1;
            data->map->tiles[player_pos->x][player_pos->y][i] -= 1;
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            do_pgt(data, i);
            return SUCCESS_STATUS;
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return ERROR_STATUS;
}

int schedule_take(data_t *data, char **args)
{
    pos_t *player_pos = data->clients[data->curr_cli_index]->player->pos;

    if (args == NULL || word_array_len(args) != 1) {
        return ERROR_STATUS;
    }
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0 &&
        is_resource_on_tile(data, i, player_pos)) {
            append_scheduler_to_queue(data, &take, args, TAKE_DELAY);
            return SUCCESS_STATUS;
        }
    }
    return ERROR_STATUS;
}
