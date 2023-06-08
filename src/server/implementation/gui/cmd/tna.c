/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** tna
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

int do_tna(data_t *data, char **args)
{
    char *result = NULL;

    if (args)
        return 1;
    for (int i = 0; data->teams[i]; i++) {
        result = strdup("tna ");
        result = concat_str(result, data->teams[i]->name);
        result = concat_str(result, "\n");
        send_to_client(data->clients, data->curr_cli_index, result);
        free(result);
        result = NULL;
    }
    return 0;
}
