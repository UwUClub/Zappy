/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

int do_msz(data_t *data, __attribute__((unused)) char **args)
{
    char *msg = NULL;

    if (args)
        return ERROR_STATUS;
    asprintf(&msg, "msz %d %d\n", data->map->width, data->map->height);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return SUCCESS_STATUS;
}
