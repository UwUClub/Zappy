/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sgt
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

int sgt(data_t *data, char **args)
{
    char *result = NULL;

    if (args)
        return 1;
    result = strdup("sgt ");
    result = concat_str(result, inttos(data->freq));
    result = concat_str(result, "\n");
    send_to_client(data->clients, data->curr_cli_index, result);
    free(result);
    return 0;
}
