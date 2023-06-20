/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

char *get_world_dimensions(data_t *data)
{
    char *result = strdup("");
    char *width_str = int_to_s(data->map->width);
    char *height_str = int_to_s(data->map->height);

    result = concat_str(result, width_str);
    result = concat_str(result, " ");
    result = concat_str(result, height_str);
    result = concat_str(result, "\n");
    free(width_str);
    free(height_str);
    return result;
}

int do_msz(data_t *data, __attribute__((unused)) char **args)
{
    char *msg = NULL;
    char *world_dimensions = NULL;

    if (args)
        return ERROR_STATUS;
    world_dimensions = get_world_dimensions(data);
    msg = strdup("msz ");
    msg = concat_str(msg, world_dimensions);
    free(world_dimensions);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return SUCCESS_STATUS;
}
