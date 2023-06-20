/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** player_cmd_scheduler
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"

void append_scheduler_to_queue(data_t *data, int (*func)(data_t *data,
    char **args), char **args, time_t delay)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    for (int i = 0; i < MAX_PENDING_CMD; i++) {
        if (player->pending_cmd_queue[i] == NULL) {
            player->pending_cmd_queue[i] = malloc(sizeof(pending_cmd_t));
            player->pending_cmd_queue[i]->func = func;
            player->pending_cmd_queue[i]->args = args;
            player->pending_cmd_queue[i]->remaining_ms =
                (delay * MS_FACTOR) / data->freq;
            break;
        }
    }
}

static int is_pending_queue_full(data_t *data)
{
    player_t *player = data->clients[data->curr_cli_index]->player;

    return player->pending_cmd_queue[MAX_PENDING_CMD - 1] != NULL;
}

static int send_ko(data_t *data, char **args)
{
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return SUCCESS_STATUS;
}

static int check_cmd_status(data_t *data, int (*func)(data_t *data,
    char **args), char **args, time_t delay)
{
    int status = 0;

    status = func(data, args);
    if (status == ERROR_STATUS) {
        append_scheduler_to_queue(data, &send_ko, NULL, delay);
        free_word_array(args);
    }
    return status;
}

int schedule_player_cmd(data_t *data, char *name, char **args)
{
    int is_freezed = data->clients[data->curr_cli_index]->player->is_freezed;

    if (is_pending_queue_full(data) || is_freezed) {
        return ERROR_STATUS;
    }
    for (int i = 0; player_schedulers[i].name != NULL; i++) {
        if (!strcmp(name, player_schedulers[i].name)) {
            return check_cmd_status(data, player_schedulers[i].func, args,
            player_schedulers[i].delay);
        }
    }
    append_scheduler_to_queue(data, &send_ko, NULL, 0);
    free_word_array(args);
    return ERROR_STATUS;
}
