/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** set
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"

static int pdr(data_t *data, int resource)
{
    char *msg = NULL;
    char *resource_str = NULL;
    char *cli_index = NULL;

    resource_str = int_to_s(resource);
    cli_index = int_to_s(data->curr_cli_index);
    msg = strdup("pdr ");
    msg = concat_str(msg, cli_index);
    msg = concat_str(msg, " ");
    msg = concat_str(msg, resource_str);
    msg = concat_str(msg, "\n");
    send_to_all_gui(data->clients, msg);
    free(cli_index);
    free(msg);
    free(resource_str);
    return 0;
}

static int set(data_t *data, char **args)
{
    const char *resource[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};

    for (int i = 0; i < 7; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && data->clients[data->curr_cli_index]->player->inventory[i] > 0) {
            data->clients[data->curr_cli_index]->player->inventory[i] -= 1;
            data->map->tiles[data->clients[data->curr_cli_index]->player->pos_y]
            [data->clients[data->curr_cli_index]->player->pos_x][i] += 1;
            pdr(data, i);
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return 0;
        }
    }
    return 1;
}

int schedule_set(data_t *data, char **args)
{
    if (args == NULL || word_array_len(args) > 1) {
        return 1;
    }
    // TODO: check if the arg is valid
    append_scheduler_to_queue(data, &set, args, SET_DELAY);
    return 0;
}
