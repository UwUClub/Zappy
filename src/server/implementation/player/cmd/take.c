/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** take
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "resources.h"

static int check_is_on_tile(data_t *data, int resource)
{
    int x = data->clients[data->curr_cli_index]->player->pos->x;
    int y = data->clients[data->curr_cli_index]->player->pos->y;
    int *tile = data->map->tiles[x][y];

    if (tile[resource] > 0) {
        data->map->tiles[x][y][resource] -= 1;
        return 0;
    }
    return 1;
}

static int pgt(data_t *data, int resource)
{
    char *msg = NULL;
    char *resource_str = NULL;
    char *cli_index = NULL;

    resource_str = int_to_s(resource);
    cli_index = int_to_s(data->curr_cli_index);
    msg = strdup("pgt ");
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

static int take(data_t *data, char **args)
{
    const char *resource[NB_RESOURCES] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};

    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0
            && check_is_on_tile(data, i) == 0) {
            data->clients[data->curr_cli_index]->player->inventory[i] += 1;
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            pgt(data, i);
            return 0;
        }
    }
    return 1;
}

int schedule_take(data_t *data, char **args)
{
    const char *resource[NB_RESOURCES] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};
    int is_resource = 1;

    if (args == NULL || word_array_len(args) != 1) {
        return 1;
    }
    // TODO: check if the arg is valid
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (strcmp(args[0], resource[i]) == 0 && 
        check_is_on_tile(data, i) == 0) {
            is_resource = 0;
        }
    }
    if (is_resource == 1) {
        return 1;
    }
    append_scheduler_to_queue(data, &take, args, TAKE_DELAY);
    return 0;
}
