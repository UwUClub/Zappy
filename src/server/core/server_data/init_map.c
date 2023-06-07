/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** init_map
*/

#include "core.h"
#include "ranges.h"

static void init_single_tile(data_t *data, int x, int y)
{

    for (int i = 0; i < TILE_SIZE; i++) {
        data->map->tiles[x][y][i] = 0;
    }
}

void init_map_tiles(data_t *data)
{
    data->map->tiles = malloc(sizeof(int *[TILE_SIZE]) * data->map->width);
    for (int x = 0; x < data->map->width; x++) {
        data->map->tiles[x] = malloc(sizeof(int [TILE_SIZE]) *
            data->map->height);
        for (int y = 0; y < data->map->height; y++) {
            init_single_tile(data, x, y);
        }
    }
}
