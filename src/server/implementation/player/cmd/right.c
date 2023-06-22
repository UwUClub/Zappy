/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** right
*/

#include "implementation.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static int move_right(data_t *data, __attribute__((unused)) char **args)
{
    if (data->clients[data->curr_cli_index]->player->orientation == WEST)
        data->clients[data->curr_cli_index]->player->orientation = NORTH;
    else
        data->clients[data->curr_cli_index]->player->orientation += 1;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    send_ppo_to_all_gui(data, data->clients[data->curr_cli_index]->player);
    return SUCCESS_STATUS;
}

int schedule_right(data_t *data, char **args)
{
    if (args != NULL) {
        return ERROR_STATUS;
    }
    append_scheduler_to_queue(data, &move_right, args, RIGHT_DELAY);
    return SUCCESS_STATUS;
}
