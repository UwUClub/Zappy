/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** enw
*/

#include "core.h"

void do_enw(data_t *data, egg_t *egg)
{
    char *msg = NULL;

    asprintf(&msg, "enw %d %d %d %d\n", egg->id, egg->progenitor_id,
        egg->pos->x, egg->pos->y);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
