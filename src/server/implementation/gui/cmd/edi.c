/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** edi
*/

#include "core.h"

void do_edi(data_t *data, const int egg_index)
{
    char *msg = NULL;

    asprintf(&msg, "edi %d\n", egg_index);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
