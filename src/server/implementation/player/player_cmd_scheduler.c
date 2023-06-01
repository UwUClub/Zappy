/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** player_cmd_scheduler
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"

static const cmd_t schedulers[] = {
    {"Forward", &schedule_forward},
    // {"Right", &schedule_right},
    // {"Left", &schedule_left},
    // {"Take", &schedule_take},
    // {"Set", &schedule_set},
    {NULL, NULL}
};

void append_scheduler_to_queue(data_t *data, int (*func)(data_t *data,
    char **args), char **args, time_t delay)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    for (int i = 0; i < MAX_PENDING_CMD; i++) {
        if (player->pending_cmd_queue[i] == NULL) {
            player->pending_cmd_queue[i] = malloc(sizeof(pending_cmd_t));
            player->pending_cmd_queue[i]->func = func;
            player->pending_cmd_queue[i]->args = args;
            player->pending_cmd_queue[i]->remaining = delay / data->freq;
            break;
        }
    }
}

static int is_pending_queue_full(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    return player->pending_cmd_queue[MAX_PENDING_CMD - 1] != NULL;
}

int schedule_player_cmd(data_t *data, char *name, char **args)
{
    if (is_pending_queue_full(data)) {
        return 84;
    }
    for (int i = 0; schedulers[i].name != NULL; i++) {
        if (!strcmp(name, schedulers[i].name)) {
            schedulers[i].func(data, args);
            break;
        }
    }
    // TODO: append ko here
}
