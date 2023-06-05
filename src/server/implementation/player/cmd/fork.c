/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** fork
*/

#include "implementation.h"
#include "player_cmd.h"

int fork_cmd(data_t *data, __attribute__((unused)) char **args)
{
    data->cli_per_team++;
    data->clients = realloc(data->clients,
        sizeof(client_t *) * (data->cli_per_team + 1));
    data->clients[data->cli_per_team] = NULL;
    data->clients[data->cli_per_team - 1] = malloc(sizeof(client_t));
    init_single_client(&(data->clients[data->cli_per_team - 1]));
    send_to_client(data->clients, data->curr_cli_index, "ok\0");
    return 0;
}

int schedule_fork(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    append_scheduler_to_queue(data, &fork_cmd, args, FORK_DELAY);
    return 0;
}
