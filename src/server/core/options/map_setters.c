/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map_setters
*/

#include <stdio.h>
#include "core.h"
#include "utils.h"

static int is_value_valid(data_t *data, char *value, char option)
{
    if (!value || !is_int(value) || atoi(value) < MIN_MAP_SIZE
    || atoi(value) > MAX_MAP_SIZE) {
        dprintf(2, "\n-%c option only accepts integer values between ",
            option);
        dprintf(2, "%d and %d\n", MIN_MAP_SIZE, MAX_MAP_SIZE);
        print_help(data, NULL);
        return 0;
    }
    return 1;
}

int set_map_width(data_t *data, char *value)
{
    if (!is_value_valid(data, value, 'x'))
        return 84;
    data->map->width = atoi(value);
    return 0;
}

int set_map_height(data_t *data, char *value)
{
    if (!is_value_valid(data, value, 'y'))
        return 84;
    data->map->height = atoi(value);
    return 0;
}
