/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** detect_server_close
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"

int detect_server_close(data_t *data)
{
    if (data->clients == NULL)
        return 1;
    for (int i = 0; data->clients[i] != NULL; i++) {
        if (is_player(data, i) == 1) {
            do_seg(data, data->clients[i]->player->team_name, 1);
        }
    }
    return 0;
}
