/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** update_tile
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"

int check_tile(data_t *data, int resource)
{
    int x = 0;
    int y = 0;
    int *tile = NULL;

    x = data->clients[data->curr_cli_index]->player->pos->x;
    y = data->clients[data->curr_cli_index]->player->pos->y;
    tile = data->map->tiles[y][x];
    return tile[resource];
}

static int remove_resource_from_tile(data_t *data,
    const unsigned int resource)
{
    int x = data->clients[data->curr_cli_index]->player->pos->x;
    int y = data->clients[data->curr_cli_index]->player->pos->y;
    int level = data->clients[data->curr_cli_index]->player->level;
    int *tile = data->map->tiles[y][x];

    if (tile[resource] > 0) {
        tile[resource] -= level_incantation[level - 1][resource];
        do_bct_to_all_gui(data, x, y);
        return 0;
    }
    return 1;
}

int remove_all_resources_from_tile(data_t *data)
{
    int x = data->clients[data->curr_cli_index]->player->pos->x;
    int y = data->clients[data->curr_cli_index]->player->pos->y;
    int *tile = data->map->tiles[y][x];
    int remove_status;

    for (int i = 1; i < TILE_SIZE; i++) {
        remove_status = remove_resource_from_tile(data, i);
        if (remove_status == 1)
            return remove_status;
    }
    return 0;
}
