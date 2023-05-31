/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** take
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

static int check_is_on_tile(data_t *data, int resource)
{
    int x = data->clients[data->curr_cli_index]->pos_x;
    int y = data->clients[data->curr_cli_index]->pos_y;
    int *tile = data->map_tiles[y][x];

    if (tile[resource] > 0) {
        data->map_tiles[y][x][resource] -= 1;
        return 0;
    }
    return 1;
}

int take(data_t *data, char **args)
{
    const char *resource[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};
    
    if (args == NULL || word_array_len(args) > 1) {
        return 1;
    }
    for (int i = 0; i < 7; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && check_is_on_tile(data, i) == 0) {
            data->clients[data->curr_cli_index]->inventory[i] += 1;
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return 0;
        }
    }
    return 1;
}
