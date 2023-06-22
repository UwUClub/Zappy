/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sgt
*/

#include "implementation.h"

void do_sgt_to_all_gui(data_t *data)
{
    char *result = NULL;

    asprintf(&result, "sgt %d\n", data->freq);
    send_to_all_gui(data->clients, result);
    free(result);
}

int do_sgt(data_t *data, char **args)
{
    char *result = NULL;

    if (args)
        return ERROR_STATUS;
    asprintf(&result, "sgt %d\n", data->freq);
    send_to_client(data->clients, data->curr_cli_index, result);
    free(result);
    return SUCCESS_STATUS;
}
