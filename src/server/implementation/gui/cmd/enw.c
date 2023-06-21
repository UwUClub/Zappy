/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** enw
*/

#include "core.h"

static char *get_enw_msg(egg_t *egg)
{
    char *msg = NULL;

    asprintf(&msg, "enw %d %d %d %d\n", egg->id, egg->progenitor_id,
        egg->pos->x, egg->pos->y);
    return msg;
}

void send_enw_to_current_cli(data_t *data, egg_t *egg)
{
    char *msg = NULL;

    msg = get_enw_msg(egg);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
}

void send_enw_to_all_gui(data_t *data, egg_t *egg)
{
    char *msg = NULL;

    msg = get_enw_msg(egg);
    send_to_all_gui(data->clients, msg);
    free(msg);
}
