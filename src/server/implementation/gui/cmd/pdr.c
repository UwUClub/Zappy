/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pdr
*/

#include "implementation.h"

int do_pdr(data_t *data, int resource)
{
    int curr_cli_id = data->clients[data->curr_cli_index]->player->id;
    char *msg = NULL;

    asprintf(&msg, "pdr %d %d\n", curr_cli_id, resource);
    send_to_all_gui(data->clients, msg);
    free(msg);
    return SUCCESS_STATUS;
}
