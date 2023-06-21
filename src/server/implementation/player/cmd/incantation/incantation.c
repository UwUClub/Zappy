/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** incantation
*/

#include "implementation.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static void rm_resources_from_tile(data_t *data, pos_t *pos,
    const int target_lvl)
{
    for (int rsrc = 1; rsrc < TILE_SIZE; rsrc++) {
        data->map->tiles[pos->x][pos->y][rsrc] -=
        elevation_secret[target_lvl - 2][rsrc + 1];
    }
    do_bct_to_all_gui(data, pos->x, pos->y);
}

static int do_incantation(data_t *data, char **args)
{
    player_t *author = data->clients[data->curr_cli_index]->player;
    const int target_lvl = author->level + 1;

    set_players_freeze_state(data->clients, author->pos, target_lvl, 0);
    if (!check_tile_for_incantation(data, author->pos, target_lvl, 0)) {
        send_ko_to_players(data->clients, author->pos, target_lvl);
        return ERROR_STATUS;
    }
    rm_resources_from_tile(data, author->pos, target_lvl);
    increment_players_level(data, author->pos, target_lvl);
    do_pie(data, author->pos, target_lvl);
    return SUCCESS_STATUS;
}

int schedule_incantation(data_t *data, char **args)
{
    player_t *author = data->clients[data->curr_cli_index]->player;

    if (args || !check_tile_for_incantation(data, author->pos,
        author->level + 1, 1)) {
        send_ko_to_players_except_current(data, author->pos,
            author->level + 1);
        return ERROR_STATUS;
    }
    set_players_freeze_state(data->clients, author->pos, author->level + 1, 1);
    do_pic(data, author);
    append_scheduler_to_queue(data, &do_incantation, args, INCANTATION_DELAY);
    send_to_client(data->clients, data->curr_cli_index, "Elevation underway\n");
    return SUCCESS_STATUS;
}
