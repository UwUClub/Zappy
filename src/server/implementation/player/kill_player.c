/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** kill_player
*/

#include "core.h"

void kill_player(data_t *data)
{
    char *msg = NULL;

    send_to_client(data->clients, data->curr_cli_index, "dead\n");
    asprintf(&msg, "pdi %d\n", data->curr_cli_index);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
