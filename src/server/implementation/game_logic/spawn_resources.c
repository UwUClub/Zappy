/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** spawn_resources
*/

#include "core.h"
#include "resources.h"
#include "ranges.h"
#include "gui_cmd.h"

static int get_nb_laying_resources(data_t *data, const int resource_id)
{
    int total = 0;

    for (int x = 0; x < data->map->width; x++) {
        for (int y = 0; y < data->map->height; y++) {
            total += data->map->tiles[x][y][resource_id];
        }
    }
    return total;
}

static void spawn_resource_type(data_t *data, const int resource_id,
    const float density)
{
    int total = data->map->width * data->map->height * density;
    int x = 0;
    int y = 0;

    total -= get_nb_laying_resources(data, resource_id);
    for (int i = 0; i < total; i++) {
        x = rand() % data->map->width;
        y = rand() % data->map->height;
        data->map->tiles[x][y][resource_id] += 1;
        send_bct_to_all_gui(data, x, y);
    }
}

static void spawn_resources(data_t *data)
{
    for (int i = FOOD; i < NB_RESOURCES; i++) {
        spawn_resource_type(data, i, resource_densities[i]);
    }
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
