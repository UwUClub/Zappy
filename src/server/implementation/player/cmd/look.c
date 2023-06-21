/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** look
*/

#include "implementation.h"
#include "player_cmd.h"
#include "utils.h"
#include <stdio.h>

static char *add_tile_content(char **look, int x, int y, data_t *data)
{
    const char *resource[7] = {"food\0", "linemate\0", "deraumere\0",
    "sibur\0", "mendiane\0", "phiras\0", "thystame\0"};
    client_t **clients = NULL;

    clients = check_player_on_tile(data, x, y);
    if (clients != NULL) {
        for (int i = 0; clients[i] != NULL; i++) {
            strcat((*look), " \0");
            strcat((*look), "player\0");
        }
    }
    free(clients);
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < data->map->tiles[x][y][i]; j++) {
            strcat((*look), " \0");
            strcat((*look), resource[i]);
        }
    }
}

static void look_front_tiles(int x, int y, data_t *data, char **look)
{
    int x_tile = 0;
    int y_tile = 0;
    int player_x = data->clients[data->curr_cli_index]->player->pos->x;
    int player_y = data->clients[data->curr_cli_index]->player->pos->y;

    strcat((*look), "[\0");
    add_tile_content(look, player_x, player_y, data);
    for (int i = 1; i <=
        data->clients[data->curr_cli_index]->player->level; i++) {
        x_tile = player_x + (x * i) + (i * y);
        y_tile = player_y + (y * i) + (i * x);
        for (int j = 0; j < i * 2 + 1; j++) {
            x_tile = calc_outbound(x_tile, data->map->width);
            y_tile = calc_outbound(y_tile, data->map->height);
            strcat((*look), ",\0");
            add_tile_content(look, x_tile, y_tile, data);
            x_tile = x_tile + y * (-1);
            y_tile = y_tile + x;
        }
    }
}

static int look(data_t *data, char **args)
{
    char *look = NULL;

    if (args != NULL)
        return ERROR_STATUS;
    look = calloc(2000, sizeof(char));
    if (data->clients[data->curr_cli_index]->player->orientation == NORTH)
        look_front_tiles(0, -1, data, &look);
    if (data->clients[data->curr_cli_index]->player->orientation == SOUTH)
        look_front_tiles(0, 1, data, &look);
    if (data->clients[data->curr_cli_index]->player->orientation == EAST)
        look_front_tiles(1, 0, data, &look);
    if (data->clients[data->curr_cli_index]->player->orientation == WEST)
        look_front_tiles(-1, 0, data, &look);
    strcat(look, "]\n\0");
    send_to_client(data->clients, data->curr_cli_index, look);
    free(look);
    return SUCCESS_STATUS;
}

int schedule_look(data_t *data, char **args)
{
    if (args != NULL)
        return ERROR_STATUS;
    append_scheduler_to_queue(data, &look, NULL, LOOK_DELAY);
    return SUCCESS_STATUS;
}
