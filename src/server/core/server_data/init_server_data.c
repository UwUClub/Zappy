/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** init_server_data
*/

#include "core.h"
#include "default_values.h"
#include "server_data.h"
#include "server_options.h"

static void set_data_default_values(data_t *data)
{
    data->curr_cli_index = -1;
    data->clients = NULL;
    data->map = malloc(sizeof(map_t));
    data->map->width = DEFAULT_MAP_WIDTH;
    data->map->height = DEFAULT_MAP_HEIGHT;
    data->map->tiles = NULL;
    data->teams = NULL;
    data->ip = DEFAULT_IP_ADDRESS;
    data->freq = DEFAULT_FREQ;
    data->port = DEFAULT_PORT;
    data->last_select_ms = 0;
    data->remaining_rsrc_spawn_ms = 0;
    init_teams(data);
}

data_t *init_server_data(int ac, char **av)
{
    data_t *data = NULL;

    data = malloc(sizeof(data_t));
    set_data_default_values(data);
    if (parse_data_options(data, ac, av))
        return NULL;
    data->clients = malloc(sizeof(client_t *));
    data->clients[0] = NULL;
    init_map_tiles(data);
    return data;
}
