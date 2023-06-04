/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** detect_win
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"

int detect_win(data_t *data)
{
    if (data->clients == NULL)
        return 0;
    for (int i = 0; data->clients[i] != NULL; i++) {
        if (is_player(data, i) == 1 && data->clients[i]->player->level == 8) {
            do_seg(data, data->clients[i]->player->team_name);
            return 1;
        }
    }
    return 0;
}
