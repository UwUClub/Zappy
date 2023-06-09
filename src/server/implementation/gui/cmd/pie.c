/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pie
*/

#include "core.h"
#include "utils.h"

void do_pie(data_t *data, pos_t *pos, const int result_lvl)
{
    char *msg = NULL;

    asprintf(&msg, "pie %d %d %d\n", pos->x, pos->y, result_lvl);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
