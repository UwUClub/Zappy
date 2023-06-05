/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** spawn_resources
*/

#include <unistd.h>
#include "core.h"
#include "resources.h"
#include "ranges.h"

static int get_nb_laying_resources(data_t *data, int resource_id)
{
    int total = 0;

    for (int i = 0; i < data->map->width; i++) {
        for (int j = 0; j < data->map->height; j++) {
            total += data->map->tiles[i][j][resource_id];
        }
    }
    return total;
}

static void spawn_resource_type(data_t *data, int resource_id, float density)
{
    int total = data->map->width * data->map->height * density;
    int x = 0;
    int y = 0;

    total -= get_nb_laying_resources(data, resource_id);
    for (int i = 0; i < total; i++) {
        x = rand() % data->map->width;
        y = rand() % data->map->height;
        data->map->tiles[x][y][resource_id] += 1;
    }
}

static void spawn_resources(data_t *data)
{
    spawn_resource_type(data, FOOD, FOOD_DENSITY);
    spawn_resource_type(data, LINEMATE, LINEMATE_DENSITY);
    spawn_resource_type(data, DERAUMERE, DERAUMERE_DENSITY);
    spawn_resource_type(data, SIBUR, SIBUR_DENSITY);
    spawn_resource_type(data, MENDIANE, MENDIANE_DENSITY);
    spawn_resource_type(data, PHIRAS, PHIRAS_DENSITY);
    spawn_resource_type(data, THYSTAME, THYSTAME_DENSITY);
}

void handle_resource_spawn(data_t *data, unsigned long long elapsed_time_ms)
{
    if (elapsed_time_ms >= data->remaining_rsrc_spawn_ms) {
        spawn_resources(data);
        data->remaining_rsrc_spawn_ms =
            (SPAWN_INTERVAL * MS_FACTOR) / data->freq;
    } else {
        data->remaining_rsrc_spawn_ms -= elapsed_time_ms;
    }
}
