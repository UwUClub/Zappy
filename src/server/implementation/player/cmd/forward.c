/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** forward
*/

#include "implementation.h"
#include "player_cmd.h"

int move_forward(data_t *data, __attribute__((unused)) char **args)
{
    if (data->clients[data->curr_cli_index]->player->orientation == NORTH)
        data->clients[data->curr_cli_index]->player->pos_y -= 1;
    if (data->clients[data->curr_cli_index]->player->orientation == SOUTH)
        data->clients[data->curr_cli_index]->player->pos_y += 1;
    if (data->clients[data->curr_cli_index]->player->orientation == EAST)
        data->clients[data->curr_cli_index]->player->pos_x += 1;
    if (data->clients[data->curr_cli_index]->player->orientation == WEST)
        data->clients[data->curr_cli_index]->player->pos_x -= 1;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    return 0;
}

int schedule_forward(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    append_scheduler_to_queue(data, &move_forward, args, FORWARD_DELAY);
    return 0;
}
