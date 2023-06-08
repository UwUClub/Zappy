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
