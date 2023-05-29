/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** spawn_resources
*/

#include <unistd.h>
#include "server_core.h"
#include "resources.h"

static void spawn_resource_type(data_t *data, int resource_id, float density)
{
    int total = data->map_width * data->map_height * density;
    int x = 0;
    int y = 0;

    for (int i = 0; i < total; i++) {
        x = rand() % data->map_width;
        y = rand() % data->map_height;
        data->map_tiles[x][y][resource_id] += 1;
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
