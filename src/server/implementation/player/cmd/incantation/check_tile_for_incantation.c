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
    // Here : the debug shows that the elevation checking is not good and maybe the elevation_secret is not fine
    // Here 2 : the debug is showing the elements is the tiles of the map, and showing some debug info about why this is not working
    for (int rsrc = 0; rsrc < TILE_SIZE; rsrc++) {
        for (int y = 0; y < map->height; y++) {
            for (int x = 0; x < map->width; x++) {
                printf("resource :%d x :%d y :%d elem:%d\n", rsrc, x, y, map->tiles[y][x][rsrc]);
                if (pos->x == x && pos->y == y && map->tiles[pos->x][pos->y][rsrc] <
                elevation_secret[target_lvl - 2][rsrc + 2]) {
                    printf("Ressource %d : not enough\n", rsrc);
                    printf("Ressource on pos x y = %d\n",map->tiles[pos->x][pos->y][rsrc]);
                    printf("Ressource needed = %d\n",elevation_secret[target_lvl - 2][rsrc + 2]);
                    printf("target_lvl - 2 = %d\nrsrc + 2 = %d\n",target_lvl - 2, rsrc + 2);
                    printf("Ressource at pos %d %d %d\n", pos->x, pos->y, map->tiles[pos->x][pos->y][rsrc]);
                    return 0;
                }
            }
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
            return 0;
        }
        if (is_valid) {
            count++;
        }
    }
    printf("Count : %d\n", count);
    return count == elevation_secret[target_lvl - 2][1];
}

int check_tile_for_incantation(data_t *data, pos_t *pos, const int target_lvl,
    const int check_ongoing_cmd)
{
    return check_resources_on_tile(data->map, pos, target_lvl) &&
        check_players_on_tile(data->clients, pos, target_lvl,
            check_ongoing_cmd);
}
