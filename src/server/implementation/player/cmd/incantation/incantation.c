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

static void set_players_freeze_state(data_t *data, pos_t *pos,
    const int target_lvl, const int new_state)
{
    for (int i = 0; data->clients[i]; i++) {
        if (is_player_valid_for_incantation(data->clients, i, pos,
        target_lvl)){
            data->clients[i]->player->is_freezed = new_state;
        }
    }
}

static void increment_players_level(data_t *data, pos_t *pos,
    const int target_lvl)
{
    char *msg = NULL;

    for (int i = 0; data->clients[i]; i++) {
        if (is_player_valid_for_incantation(data->clients, i, pos,
        target_lvl)){
            data->clients[i]->player->level = target_lvl;
            send_plv_to_all_gui(data, data->clients[i]->player);
            asprintf(&msg, "Current level: %d\n", target_lvl);
            send_to_client(data->clients, i, msg);
            free(msg);
        }
    }
}

static int do_incantation(data_t *data, char **args)
{
    player_t *author = data->clients[data->curr_cli_index]->player;
    const int target_lvl = author->level + 1;

    set_players_freeze_state(data, author->pos, target_lvl, 0);
    if (!check_tile_for_incantation(data, author->pos, target_lvl, 0)) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 1;
    }
    rm_resources_from_tile(data, author->pos, target_lvl);
    increment_players_level(data, author->pos, target_lvl);
    do_pie(data, author->pos, target_lvl);
    return 0;
}

int schedule_incantation(data_t *data, char **args)
{
    player_t *author = data->clients[data->curr_cli_index]->player;

    if (args || !check_tile_for_incantation(data, author->pos,
        author->level + 1, 1)) {
        return 1;
    }
    set_players_freeze_state(data, author->pos, author->level + 1, 1);
    do_pic(data, author);
    append_scheduler_to_queue(data, &do_incantation, args, INCANTATION_DELAY);
    return 0;
}
