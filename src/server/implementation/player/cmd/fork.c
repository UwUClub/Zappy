/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** fork
*/

#include "implementation.h"
#include "player_cmd.h"

static int fork_cmd(data_t *data, __attribute__((unused)) char **args)
{
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
