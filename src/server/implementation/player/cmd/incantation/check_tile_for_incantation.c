/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** check_tile_for_incantation
*/

#include "implementation.h"
#include "player_cmd.h"

static int check_resources_on_tile(map_t *map, pos_t *pos,
    const int target_lvl)
{
    for (int rsrc = 1; rsrc < TILE_SIZE; rsrc++) {
        if (map->tiles[pos->x][pos->y][rsrc] <
            elevation_secret[target_lvl - 2][rsrc + 1]) {
            return SUCCESS_STATUS;
        }
    }
    return 1;
}

int is_player_valid_for_incantation(client_t **clients, const int index,
    pos_t *pos, const int target_lvl)
{
    return is_player(clients, index) &&
        clients[index]->player->pos->x == pos->x &&
        clients[index]->player->pos->y == pos->y &&
        clients[index]->player->level == target_lvl - 1;
}

static int check_players_on_tile(client_t **clients, pos_t *pos,
    const int target_lvl, const int check_ongoing_cmd)
{
    int count = 0;
    int is_valid = 0;

    for (int i = 0; clients[i]; i++) {
        is_valid = is_player_valid_for_incantation(clients, i, pos, target_lvl);
        if (check_ongoing_cmd && is_valid &&
            clients[i]->player->pending_cmd_queue[0]) {
            return SUCCESS_STATUS;
        }
        if (is_valid) {
            count++;
        }
    }
    return count == elevation_secret[target_lvl - 2][1];
}

int check_tile_for_incantation(data_t *data, pos_t *pos, const int target_lvl,
    const int check_ongoing_cmd)
{
    return check_resources_on_tile(data->map, pos, target_lvl) &&
        check_players_on_tile(data->clients, pos, target_lvl,
            check_ongoing_cmd);
}
