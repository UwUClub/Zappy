/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

int msz(data_t *data, char **args)
{
    char *msg = strdup("msz ");
    char *width_str = inttos(data->map->width);
    char *height_str = inttos(data->map->height);
    
    msg = concat_str(msg, width_str);
    msg = concat_str(msg, " ");
    msg = concat_str(msg, height_str);
    msg = concat_str(msg, "\n");
    free(width_str);
    free(height_str);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}
