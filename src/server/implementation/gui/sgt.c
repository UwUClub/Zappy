/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sgt
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

int do_sgt(data_t *data, char **args)
{
    char *result = NULL;
    char *freq_str = NULL;

    if (args)
        return 1;
    result = strdup("sgt ");
    freq_str = int_to_s(data->freq);
    result = concat_str(result, freq_str);
    result = concat_str(result, "\n");
    send_to_client(data->clients, data->curr_cli_index, result);
    free(freq_str);
    free(result);
    return 0;
}
