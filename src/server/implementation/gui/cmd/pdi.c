/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pdi
*/

#include "core.h"

void do_pdi(data_t *data, const int player_id)
{
    char *msg = NULL;

    asprintf(&msg, "pdi %d\n", player_id);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
