/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map_setters
*/

#include "server_core.h"

void set_map_width(data_t *data, char *value)
{
    data->map_width = atoi(value);
}

void set_map_height(data_t *data, char *value)
{
    data->map_height = atoi(value);
}
