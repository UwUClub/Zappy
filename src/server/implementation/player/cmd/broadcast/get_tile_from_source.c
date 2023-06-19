/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_tile_from_source
*/

#include "core.h"

static int get_tile_if_x_negative(int dir_y)
{
    if (dir_y < 0)
        return 2;
    if (dir_y == 0)
        return 3;
    if (dir_y > 0)
        return 4;
    return -1;
}

static int get_tile_if_x_0(int dir_y)
{
    if (dir_y < 0)
        return 1;
    if (dir_y > 0)
        return 5;
    return -1;
}

static int get_tile_if_x_positive(int dir_y)
{
    if (dir_y < 0)
        return 8;
    if (dir_y == 0)
        return 7;
    if (dir_y > 0)
        return 6;
    return -1;
}

static int get_tile_from_dir(orientation_t orientation, int dir_x,
    int dir_y)
{
    int result = 1;

    if (dir_x < 0)
        result = get_tile_if_x_negative(dir_y);
    if (dir_x == 0)
        result = get_tile_if_x_0(dir_y);
    if (dir_x > 0)
        result = get_tile_if_x_positive(dir_y);
    for (int i = 1; i < orientation; i++) {
        result += 2;
    }
    while (result > 8) {
        result -= 8;
    }
    return result;
}

int get_tile_from_source(data_t *data, const unsigned int player_id,
    const unsigned int source_x, const unsigned int source_y)
{
    player_t *player = data->clients[player_id]->player;
    int dir_x = source_x - player->pos->x;
    int dir_y = source_y - player->pos->y;

    if (dir_x > data->map->width / 2)
        dir_x -= data->map->width;
    else if (dir_x < -data->map->width / 2)
        dir_x += data->map->width;
    if (dir_y > data->map->height / 2)
        dir_y -= data->map->height;
    else if (dir_y < -data->map->height / 2)
        dir_y += data->map->height;
    return get_tile_from_dir(player->orientation, dir_x, dir_y);
}
