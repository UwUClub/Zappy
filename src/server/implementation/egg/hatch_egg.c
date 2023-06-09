/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** hatch_egg
*/

#include "core.h"
#include "gui_cmd.h"
#include "server_data.h"

void hatch_egg(data_t *data, const int team_index, const int egg_index)
{
    const int id = data->teams[team_index]->eggs[egg_index]->id;

    free_egg(data->teams[team_index]->eggs[egg_index]);
    for (int i = egg_index; data->teams[team_index]->eggs[i]; i++) {
        data->teams[team_index]->eggs[i] = data->teams[team_index]->eggs[i + 1];
    }
    do_edi(data, id);
}

static void hatch_single_egg_at_pos(data_t *data, const int team_index,
    const int egg_index, pos_t *pos)
{
    if (data->teams[team_index]->eggs[egg_index]->pos->x == pos->x &&
        data->teams[team_index]->eggs[egg_index]->pos->y == pos->y) {
        hatch_egg(data, team_index, egg_index);
    }
}

void hatch_eggs_at_pos(data_t *data, pos_t *pos)
{
    for (int i = 0; data->teams[i]; i++) {
        for (int j = 0; data->teams[i]->eggs[j]; j++) {
            hatch_single_egg_at_pos(data, i, j, pos);
        }
    }
}
