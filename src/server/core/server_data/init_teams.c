/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** init_teams
*/

#include "core.h"
#include "ranges.h"
#include "default_values.h"
#include "utils.h"
#include "resources.h"

static egg_t *init_egg(data_t *data)
{
    egg_t *egg = NULL;

    egg = malloc(sizeof(egg_t));
    egg->id = data->nb_slots;
    data->nb_slots++;
    egg->progenitor_id = 0;
    egg->pos = malloc(sizeof(pos_t));
    egg->pos->x = rand() % data->map->width;
    egg->pos->y = rand() % data->map->height;
    egg->remaining_digestion_ms = 0;
    egg->food = FOOD_START;
    return egg;
}

void init_teams(data_t *data, char **team_names,
    const unsigned int nb_egg_per_team)
{
    int nb_teams = 0;

    nb_teams = word_array_len(team_names);
    data->teams = malloc(sizeof(team_t *) * (nb_teams + 1));
    for (int i = 0; i < nb_teams; i++) {
        data->teams[i] = malloc(sizeof(team_t));
        data->teams[i]->name = strdup(team_names[i]);
        data->teams[i]->eggs = malloc(sizeof(egg_t *) * (nb_egg_per_team + 1));
        for (int j = 0; j < nb_egg_per_team; j++) {
            data->teams[i]->eggs[j] = init_egg(data);
        }
        data->teams[i]->eggs[nb_egg_per_team] = NULL;
    }
    data->teams[nb_teams] = NULL;
}
