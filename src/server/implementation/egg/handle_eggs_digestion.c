/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_eggs_digestion
*/

#include "core.h"
#include "implementation.h"
#include "resources.h"

static void handle_single_egg_digestion(data_t *data, const int team_index,
    const int egg_index, unsigned long long elapsed_time_ms)
{
    egg_t *egg = data->teams[team_index]->eggs[egg_index];

    if (elapsed_time_ms >= egg->remaining_digestion_ms) {
        if (egg->food > 0) {
            egg->food--;
            egg->remaining_digestion_ms = (DIGESTION_TIME * MS_FACTOR)
                / data->freq;
        } else {
            hatch_egg(data, team_index, egg_index);
        }
    } else {
        egg->remaining_digestion_ms -= elapsed_time_ms;
    }
}

void handle_eggs_digestion(data_t *data, unsigned long long elapsed_time_ms)
{
    for (int i = 0; data->teams[i]; i++) {
        for (int j = 0; data->teams[i]->eggs[j]; j++) {
            handle_single_egg_digestion(data, i, j, elapsed_time_ms);
        }
    }
}
