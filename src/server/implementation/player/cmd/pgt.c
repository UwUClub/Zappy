/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pgt
*/

#include "core.h"

int do_pgt(data_t *data, int resource)
{
    int curr_cli_id = data->clients[data->curr_cli_index]->player->id;
    char *msg = NULL;

    asprintf(&msg, "pgt %d %d\n", curr_cli_id, resource);
    send_to_all_gui(data->clients, msg);
    free(msg);
    return SUCCESS_STATUS;
}
