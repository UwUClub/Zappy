/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** update_tile
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"

int check_tile(data_t *data, int ressource)
{
    int x = 0;
    int y = 0;
    int *tile = NULL;

    x = data->clients[data->curr_cli_index]->player->pos_x;
    y = data->clients[data->curr_cli_index]->player->pos_y;
    tile = data->map->tiles[y][x];
    return tile[ressource];
}

static void send_bct_to_all_gui(data_t *data)
{
    int x = data->clients[data->curr_cli_index]->player->pos_x;
    int y = data->clients[data->curr_cli_index]->player->pos_y;
    char **msg = NULL;

    msg = malloc(sizeof(char *) * 3);
    if (!msg)
        return;
    asprintf(&msg[0], "%d", x);
    asprintf(&msg[1], "%d", y);
    msg[2] = NULL;
    do_bct_to_all_gui(data, msg);
    free(msg[0]);
    free(msg[1]);
    free(msg);
}


static int remove_ressource_from_tile(data_t *data,
    const unsigned int ressource)
{
    int x = data->clients[data->curr_cli_index]->player->pos_x;
    int y = data->clients[data->curr_cli_index]->player->pos_y;
    int level = data->clients[data->curr_cli_index]->player->level;
    int *tile = data->map->tiles[y][x];

    if (tile[ressource] > 0) {
        tile[ressource] -= level_incantation[level - 1][ressource];
        send_bct_to_all_gui(data);
        return 0;
    }
    return 1;
}

int remove_all_ressources_from_tile(data_t *data)
{
    int x = data->clients[data->curr_cli_index]->player->pos_x;
    int y = data->clients[data->curr_cli_index]->player->pos_y;
    int *tile = data->map->tiles[y][x];
    int remove_status;

    for (int i = 1; i < TILE_SIZE; i++) {
        remove_status = remove_ressource_from_tile(data, i);
        if (remove_status == 1)
            return remove_status;
    }
    return 0;
}
