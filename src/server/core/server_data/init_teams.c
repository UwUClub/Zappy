/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** init_teams
*/

#include "core.h"
#include "ranges.h"
#include "default_values.h"

void init_teams(data_t *data)
{
    data->teams = malloc(sizeof(team_t *) * (MAX_TEAMS + 1));
    for (int i = 0; i < MAX_TEAMS; i++) {
        data->teams[i] = malloc(sizeof(team_t));
        asprintf(&data->teams[i]->name, "%s%d", DEFAULT_TEAM_NAME, i + 1);
        data->teams[i]->nb_cli = DEFAULT_CLI_PER_TEAM;
        data->teams[i]->eggs = malloc(sizeof(pos_t *));
        data->teams[i]->eggs[0] = NULL;
    }
    data->teams[MAX_TEAMS] = NULL;
}
