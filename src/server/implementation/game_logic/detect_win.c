/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** detect_win
*/

#include "implementation.h"
#include "default_values.h"
#include "utils.h"
#include "gui_cmd.h"

int detect_win(data_t *data)
{
    if (data->clients == NULL)
        return SUCCESS_STATUS;
    for (int i = 0; data->clients[i] != NULL; i++) {
        if (is_player(data->clients, i) &&
            data->clients[i]->player->level == MAX_LEVEL) {
            do_seg(data, data->clients[i]->player->team_name);
            return 1;
        }
    }
    return SUCCESS_STATUS;
}
