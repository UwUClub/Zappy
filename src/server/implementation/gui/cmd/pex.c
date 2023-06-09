/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pex
*/

#include "core.h"

int do_pex(data_t *data, const int player_id)
{
    char *msg = NULL;

    asprintf(&msg, "pex %d\n", player_id);
    send_to_all_gui(data->clients, msg);
    free(msg);
    return 0;
}
