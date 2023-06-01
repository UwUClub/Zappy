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

static int send_to_all_gui(char *msg, client_t **clients)
{
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->fd != -1
            && clients[i]->team_name != NULL &&
            strcmp(clients[i]->team_name, "GRAPHIC") == 0) {
                send_to_client(clients, i, msg);
        }
    }
    return 0;
}

static int pgt(data_t *data, int resource)
{
    char *msg = NULL;
    char *resource_str = NULL;
    char *cli_index = NULL;

    resource_str = int_to_s(resource);
    cli_index = int_to_s(data->curr_cli_index);
    msg = strdup("pgt ");
    msg = concat_str(msg, cli_index);
    msg = concat_str(msg, " ");
    msg = concat_str(msg, resource_str);
    msg = concat_str(msg, "\n");
    send_to_all_gui(msg, data->clients);
    free(cli_index);
    free(msg);
    free(resource_str);
    return 0;
}

int take(data_t *data, char **args)
{
    const char *resource[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};
    if (args == NULL || word_array_len(args) != 1) {
        return 1;
    }
    for (int i = 0; i < 7; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && check_is_on_tile(data, i) == 0) {
            data->clients[data->curr_cli_index]->inventory[i] += 1;
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            pgt(data, i);
            return 0;
        }
    }
    return 1;
}
