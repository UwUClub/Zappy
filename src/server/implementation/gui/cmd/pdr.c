/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pdr
*/

#include "implementation.h"

int do_pdr(data_t *data, int resource)
{
    char *msg = NULL;

    asprintf(&msg, "pdr %d %d\n", data->curr_cli_index, resource);
    send_to_all_gui(data->clients, msg);
    free(msg);
    return SUCCESS_STATUS;
}
