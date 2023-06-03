/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** seg
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

static void print_seg_ctrl_c(data_t *data, char *msg)
{
    for (int i = 0; data->clients[i] != NULL; i++) {
        if (is_player(data, i) == 0) {
                dprintf(data->clients[i]->fd, "%s", msg);
        }
    }
}

int do_seg(data_t *data, const char *team_name, const int is_ctrl_c)
{
    char *msg = NULL;

    if (team_name == NULL)
        return 1;
    msg = strdup("seg ");
    msg = concat_str(msg, team_name);
    msg = concat_str(msg, "\n");
    if (is_ctrl_c == 1)
        print_seg_ctrl_c(data, msg);
    else
        send_to_all_gui(data->clients, msg);
    free(msg);
    return 0;
}
