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

egg_t *init_egg(data_t *data, const unsigned int pos_x,
    const unsigned int pos_y)
{
    egg_t *egg = NULL;

    egg = malloc(sizeof(egg_t));
    egg->id = data->nb_slots;
    data->nb_slots++;
    egg->progenitor_id = data->curr_cli_index;
    egg->pos = malloc(sizeof(pos_t));
    egg->pos->x = pos_x;
    egg->pos->y = pos_y;
    egg->remaining_digestion_ms = 0;
    egg->food = FOOD_START;
    return egg;
}

static egg_t **init_eggs(data_t *data, const unsigned int length)
{
    egg_t **eggs = NULL;
    int x = 0;
    int y = 0;

    eggs = malloc(sizeof(egg_t *) * (length + 1));
    for (int i = 0; i < length; i++) {
        x = rand() % data->map->width;
        y = rand() % data->map->height;
        eggs[i] = init_egg(data, x, y);
    }
    eggs[length] = NULL;
    return eggs;
}

void init_teams(data_t *data, char **team_names,
    const unsigned int nb_egg_per_team)
{
    int nb_teams = 0;
    int x = 0;
    int y = 0;

    nb_teams = word_array_len(team_names);
    data->teams = malloc(sizeof(team_t *) * (nb_teams + 1));
    for (int i = 0; i < nb_teams; i++) {
        data->teams[i] = malloc(sizeof(team_t));
        data->teams[i]->name = strdup(team_names[i]);
        data->teams[i]->eggs = init_eggs(data, nb_egg_per_team);
    }
    data->teams[nb_teams] = NULL;
}
