/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pgt
*/

#include "core.h"

int do_pgt(data_t *data, int resource)
{
    char *msg = NULL;

    asprintf(&msg, "pgt %d %d\n", data->curr_cli_index, resource);
    send_to_all_gui(data->clients, msg);
    free(msg);
    return 0;
}
