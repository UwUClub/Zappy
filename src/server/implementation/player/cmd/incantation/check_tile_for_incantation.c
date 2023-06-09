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
    for (int rsrc = 0; rsrc < TILE_SIZE; rsrc++) {
        if (map->tiles[pos->x][pos->y][rsrc] <=
            elevation_secret[target_lvl - 2][rsrc + 2]) {
            return 0;
        }
    }
    return 1;
}

static int check_players_on_tile(client_t **clients, pos_t *pos,
    const int target_lvl)
{
    int count = 0;

    for (int i = 0; clients[i]; i++) {
        if (is_player(clients, i) &&
            clients[i]->player->pos->x == pos->x &&
            clients[i]->player->pos->y == pos->y &&
            clients[i]->player->level == target_lvl - 1) {
            count++;
        }
    }
    return count == elevation_secret[target_lvl - 2][1];
}

int check_tile_for_incantation(data_t *data, pos_t *pos, const int target_lvl)
{
    return check_resources_on_tile(data->map, pos, target_lvl) &&
        check_players_on_tile(data->clients, pos, target_lvl);
}
