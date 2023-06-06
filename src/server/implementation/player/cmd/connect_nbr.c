/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** connect_nbr
*/

#include "implementation.h"
#include "player_cmd.h"
#include "utils.h"

static int connect_nbr(data_t *data, __attribute__((unused)) char **args)
{
    int nb = 0;
    char *msg = NULL;

    nb = get_remaining_slots(data,
    data->clients[data->curr_cli_index]->player->team_name);
    asprintf(&msg, "%d\n", nb);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}

int schedule_connect_nbr(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    append_scheduler_to_queue(data, &connect_nbr, args, CONNECT_NBR_DELAY);
    return 0;
}
