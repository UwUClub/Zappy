/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_team
*/

#include "core.h"

team_t *get_team_by_name(team_t **teams, const char *name)
{
    for (int i = 0; teams[i]; i++) {
        if (!strcmp(teams[i]->name, name)) {
            return teams[i];
        }
    }
    return NULL;
}

int get_nb_eggs(data_t *data, const char *team_name)
{
    team_t *team = NULL;
    int result = 0;

    team = get_team_by_name(data->teams, team_name);
    for (int i = 0; team->eggs[i]; i++) {
        result++;
    }
    return result;
}
