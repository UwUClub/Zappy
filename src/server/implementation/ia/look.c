/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** look
*/

#include "server_implementation.h"
#include <stdio.h>

static char *add_tile_content(char **look, int x, int y, data_t *data)
{
    const char *resource[7] = {"food\0", "linemate\0", "deraumere\0",
    "sibur\0", "mendiane\0", "phiras\0", "thystame\0"};
    client_t **clients = check_player_on_tile(data, x, y);

    if (clients != NULL) {
        for (int i = 0; clients[i] != NULL; i++) {
            strcat((*look), " \0");
            strcat((*look), "player\0");
        }
    }
    free(clients);
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < data->map_tiles[y][x][i]; j++) {
            strcat((*look), " \0");
            strcat((*look), resource[i]);
        }
    }
    strcat((*look), ",\0");
}

static int calc_outbound(int value, int max)
{
    if (value < 0)
        return max + value;
    if (value >= max)
        return value - max;
    return value;
}

void look_front_tiles(int x, int y, data_t *data, char **look)
{
    int x_tile = 0;
    int y_tile = 0;
    int player_x = data->clients[data->curr_cli_index]->pos_x;
    int player_y = data->clients[data->curr_cli_index]->pos_y;

    strcat((*look), "[\0");
    add_tile_content(look, player_x, player_y, data);
    for (int i = 1; i <= data->clients[data->curr_cli_index]->level; i++) {
        x_tile = player_x + (x * i) + (i * y);
        y_tile = player_y + (y * i) + (i * x);
        for (int j = 0; j < i * 2 + 1; j++) {
            x_tile = x_tile + y * (-1);
            y_tile = y_tile + x;
            x_tile = calc_outbound(x_tile, data->map_width);
            y_tile = calc_outbound(y_tile, data->map_height);
            add_tile_content(look, x_tile, y_tile, data);
        }
    }
    strcat((*look), "]\n\0");
}

int look(data_t *data, char **args)
{
    char *look = NULL;

    if (args != NULL)
        return 1;
    look = calloc(2000, sizeof(char));
    if (data->clients[data->curr_cli_index]->orientation == NORTH)
        look_front_tiles(0, -1, data, &look);
    if (data->clients[data->curr_cli_index]->orientation == SOUTH)
        look_front_tiles(0, 1, data, &look);
    if (data->clients[data->curr_cli_index]->orientation == EAST)
        look_front_tiles(1, 0, data, &look);
    if (data->clients[data->curr_cli_index]->orientation == WEST)
        look_front_tiles(-1, 0, data, &look);
    send_to_client(data->clients, data->curr_cli_index, look);
    free(look);
    return 0;
}
