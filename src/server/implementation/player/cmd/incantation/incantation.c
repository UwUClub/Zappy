/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** incantation
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static int check_resources(data_t *data, const unsigned int level_index)
{
    for (int i = 1; i < TILE_SIZE; i++) {
        if (check_tile(data, i) <= level_incantation[level_index][i])
            return 1;
    }
    return 0;
}

static int check_incantation(data_t *data)
{
    int level = 0;
    int status = 0;

    level = data->clients[data->curr_cli_index]->player->level;
    for (int i = 0; i < NB_LEVELS - 1; i++) {
        if (level == level_incantation[i][0]) {
            status = check_resources(data, i);
        }
        if (status == 1)
            return status;
    }
    return status;
}

static int do_incantation(data_t *data, char **args)
{
    client_t *client = NULL;

    client = data->clients[data->curr_cli_index];
    if (client->player->level == NB_LEVELS) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 1;
    } else {
        if (check_incantation(data) == 0) {
            client->player->level += 1;
            send_plv_to_all_gui(data, client->player);
            remove_all_resources_from_tile(data);
        } else {
            send_to_client(data->clients, data->curr_cli_index, "ko\n");
            return 1;
        }
    }
    return 0;
}

int schedule_incantation(data_t *data, char **args)
{
    int can_incant = 0;

    if (args)
        return 1;
    can_incant = check_incantation(data);
    if (can_incant == 1) {
        return 1;
    }
    append_scheduler_to_queue(data, &do_incantation, args,
    INCANTATION_DELAY);
    return 0;
}
