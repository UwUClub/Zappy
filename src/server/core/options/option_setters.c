/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** option_setters
*/

#include "core.h"
#include "utils.h"
#include "server_options.h"
#include "server_data.h"
#include "default_values.h"

int set_port(data_t *data, char *value)
{
    data->port = atoi(value);
    return 0;
}

int set_team_names(data_t *data, char *value)
{
    char **team_names = NULL;
    int nb_teams = 0;

    free_teams(data);
    data->teams = NULL;
    team_names = str_to_word_array(value, " ");
    nb_teams = word_array_len(team_names);
    data->teams = malloc(sizeof(team_t *) * (nb_teams + 1));
    for (int i = 0; i < nb_teams; i++) {
        data->teams[i] = malloc(sizeof(team_t));
        data->teams[i]->name = strdup(team_names[i]);
        data->teams[i]->nb_cli = DEFAULT_CLI_PER_TEAM;
        data->teams[i]->eggs = malloc(sizeof(pos_t *));
        data->teams[i]->eggs[0] = NULL;
    }
    data->teams[nb_teams] = NULL;
    free_word_array(team_names);
    return 0;
}

int set_cli_per_team(data_t *data, char *value)
{
    if (!value || !is_int(value) || atoi(value) < 1) {
        dprintf(2, "\n-c option only accepts integer values ");
        dprintf(2, "greater or equal to 1\n");
        print_help(data, NULL);
        return 84;
    }
    for (int i = 0; data->teams[i]; i++) {
        data->teams[i]->nb_cli = atoi(value);
    }
    return 0;
}

int set_freq(data_t *data, char *value)
{
    if (!value || !is_int(value) || atoi(value) < MIN_FREQ
    || atoi(value) > MAX_FREQ) {
        dprintf(2, "\n-f option only accepts integer values between ");
        dprintf(2, "%i and %i\n", MIN_FREQ, MAX_FREQ);
        print_help(data, NULL);
        return 84;
    }
    data->freq = atoi(value);
    return 0;
}

int set_ip(data_t *data, char *value)
{
    if (!value || !is_ip(value)) {
        dprintf(2, "\n-v option only accepts valid IPv4 addresses\n");
        print_help(data, NULL);
        return 84;
    }
    data->ip = strdup(value);
    return 0;
}
