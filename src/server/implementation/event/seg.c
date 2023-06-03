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
        if (data->clients[i]->fd != -1 && data->clients[i]->is_registered == 1
            && data->clients[i]->player == NULL) {
                dprintf(data->clients[i]->fd, "%s", msg);
        }
    }
}

static int do_seg(data_t *data, const char *team_name, int is_ctrl_c)
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

static int is_player(data_t *data, int i)
{
    if (data->clients[i]->fd != -1 && data->clients[i]->is_registered == 1 &&
        data->clients[i]->player != NULL &&
        data->clients[i]->player->team_name != NULL) {
            return 1;
    }
    return 0;
}

int detect_win(data_t *data, int is_ctrl_c)
{
    if (data->clients == NULL)
        return 1;
    for (int i = 0; data->clients[i] != NULL; i++) {
        if (is_ctrl_c == 1 && is_player(data, i) == 1) {
            do_seg(data, data->clients[i]->player->team_name, 1);
        }
        if (is_player(data, i) == 1 && data->clients[i]->player->level == 8) {
                do_seg(data, data->clients[i]->player->team_name, 0);
        }
    }
    return 0;
}
