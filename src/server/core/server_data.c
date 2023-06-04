/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** server_data
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core.h"
#include "utils.h"

static void set_data_default_values(data_t *data)
{
    data->curr_cli_index = -1;
    data->clients = NULL;
    data->map = malloc(sizeof(map_t));
    data->map->width = 10;
    data->map->height = 10;
    data->map->tiles = NULL;
    data->team_names = NULL;
    data->cli_per_team = 2;
    data->freq = 100;
    data->port = 4242;
    data->ip = "127.0.0.1";
}

static void init_single_tile(data_t *data, int x, int y)
{
    for (int i = 0; i < TILE_SIZE; i++) {
        data->map->tiles[x][y][i] = 0;
    }
}

static void init_map_tiles(data_t *data)
{
    data->map->tiles = malloc(sizeof(int *[7]) * data->map->height);
    for (int x = 0; x < data->map->height; x++) {
        data->map->tiles[x] = malloc(sizeof(int [7]) * data->map->width);
        for (int y = 0; y < data->map->width; y++) {
            init_single_tile(data, x, y);
        }
    }
    spawn_resources(data);
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
    if (!data->team_names) {
        data->team_names = malloc(sizeof(char *) * 5);
        data->team_names[0] = strdup("Team1");
        data->team_names[1] = strdup("Team2");
        data->team_names[2] = strdup("Team3");
        data->team_names[3] = strdup("Team4");
        data->team_names[4] = NULL;
    }
    init_map_tiles(data);
    return data;
}

void free_server_data(data_t *data)
{
    close_clients(data->clients);
    free_word_array(data->team_names);
    if (data->map) {
        for (int x = 0; x < data->map->height; x++) {
            free(data->map->tiles[x]);
        }
        free(data->map->tiles);
        free(data->map);
    }
    free(data);
}
