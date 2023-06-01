/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** set
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

int set(data_t *data, char **args)
{
    const char *resource[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};

    if (args == NULL || word_array_len(args) > 1) {
        return 1;
    }
    for (int i = 0; i < 7; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && data->clients[data->curr_cli_index]->player->inventory[i] > 0) {
            data->clients[data->curr_cli_index]->player->inventory[i] -= 1;
            data->map->tiles[data->clients[data->curr_cli_index]->player->pos_y]
            [data->clients[data->curr_cli_index]->player->pos_x][i] += 1;
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return 0;
        }
    }
    return 1;
}
