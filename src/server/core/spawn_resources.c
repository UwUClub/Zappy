/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** spawn_resources
*/

#include <unistd.h>
#include "core.h"
#include "resources.h"

static void spawn_resource_type(data_t *data, int resource_id, float density)
{
    int total = data->map->width * data->map->height * density;
    int x = 0;
    int y = 0;

    for (int i = 0; i < total; i++) {
        x = rand() % data->map->width;
        y = rand() % data->map->height;
        data->map->tiles[x][y][resource_id] += 1;
    }
}

void spawn_resources(data_t *data)
{
    spawn_resource_type(data, FOOD, FOOD_DENSITY);
    spawn_resource_type(data, LINEMATE, LINEMATE_DENSITY);
    spawn_resource_type(data, DERAUMERE, DERAUMERE_DENSITY);
    spawn_resource_type(data, SIBUR, SIBUR_DENSITY);
    spawn_resource_type(data, MENDIANE, MENDIANE_DENSITY);
    spawn_resource_type(data, PHIRAS, PHIRAS_DENSITY);
    spawn_resource_type(data, THYSTAME, THYSTAME_DENSITY);
}
