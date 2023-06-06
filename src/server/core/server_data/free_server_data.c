/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** free_server_data
*/

#include "core.h"

void free_teams(data_t *data)
{
    if (!data->teams)
        return;
    for (int i = 0; data->teams[i]; i++) {
        free(data->teams[i]->name);
        for (int j = 0; data->teams[i]->eggs[j]; j++) {
            free(data->teams[i]->eggs[j]->pos);
            free(data->teams[i]->eggs[j]);
        }
        free(data->teams[i]->eggs);
        free(data->teams[i]);
    }
    free(data->teams);
}

void free_server_data(data_t *data)
{
    close_clients(data->clients);
    free_teams(data);
    if (data->map) {
        for (int x = 0; x < data->map->height; x++) {
            free(data->map->tiles[x]);
        }
        free(data->map->tiles);
        free(data->map);
    }
    free(data);
}
