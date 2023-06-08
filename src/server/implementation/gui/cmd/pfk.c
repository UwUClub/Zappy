/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pfk
*/

#include "core.h"

void do_pfk(data_t *data, const unsigned int player_id)
{
    char *msg = NULL;

    asprintf(&msg, "pfk %d\n", player_id);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
