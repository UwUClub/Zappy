/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pic
*/

#include "core.h"

void do_pic(data_t *data, pos_t *pos, const int lvl, )
{
    char *msg = NULL;

    asprintf(&msg, "pic %d %d%s\n", x, y, resources);
    send_to_all_gui(data->clients, msg);
    free(resources);
    free(msg);
    return 0;
}