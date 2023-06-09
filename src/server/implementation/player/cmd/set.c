/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** set
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"
#include "resources.h"

static int set(data_t *data, char **args)
{
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && data->clients[data->curr_cli_index]->player->inventory[i] > 0) {
            data->clients[data->curr_cli_index]->player->inventory[i] -= 1;
            data->map->tiles[data->clients[data->curr_cli_index]->player->
            pos->x][data->clients[data->curr_cli_index]->player->pos->y]
            [i] += 1;
            do_pdr(data, i);
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return 0;
        }
    }
    return 1;
}

int schedule_set(data_t *data, char **args)
{
    if (args == NULL || word_array_len(args) > 1) {
        return 1;
    }
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0 &&
        data->clients[data->curr_cli_index]->player->inventory[i] > 0) {
            append_scheduler_to_queue(data, &set, args, SET_DELAY);
            return 0;
        }
    }
    return 1;
}
