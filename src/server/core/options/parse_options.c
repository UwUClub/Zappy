/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** parse_options
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server_core.h"
#include "utils.h"

static const option_t options[] = {
    { 'h', &print_help },
    { 'p', &set_port },
    { 'x', &set_map_width },
    { 'y', &set_map_height },
    { 'c', &set_cli_per_team },
    { 'f', &set_freq },
    { -1, NULL }
};

static void parse_team_names(data_t *data, int ac, char **av)
{
    char *teams = NULL;

    teams = strdup("");
    optind--;
    for (; optind < ac && *av[optind] != '-'; optind++) {
        teams = concat_str(teams, av[optind]);
        teams = concat_str(teams, " ");
    }
    data->team_names = str_to_word_array(teams, " ");
    free(teams);
}

static int parse_single_option(int option, data_t *data, int ac,
    char **av)
{
    for (int i = 0; options[i].flag != -1; i++) {
        if (options[i].flag == option)
            options[i].func(data, optarg);
    }
    return option == 'h';
}

static int parse_data_options(data_t *data, int ac, char **av)
{
    int option = 0;

    while (option != -1) {
        option = getopt(ac, av, "hp:x:y:n:c:f");
        if (parse_single_option(option, data, ac, av))
            return 1;
    }
    return 0;
}

static void set_data_default_values(data_t *data)
{
    data->curr_cli_index = -1;
    data->map_width = 10;
    data->map_height = 10;
    data->cli_per_team = 2;
    data->freq = 7;
    data->port = 4242;
    data->clients = NULL;
    data->team_names = NULL;
}

data_t *init_data(int ac, char **av)
{
    data_t *data = NULL;

    data = malloc(sizeof(data_t));
    set_data_default_values(data);
    if (parse_data_options(data, ac, av))
        return NULL;
    if (!data->clients)
        data->clients = init_clients(MAX_TEAMS * data->cli_per_team);
    if (!data->team_names) {
        data->team_names = malloc(sizeof(char *) * 3);
        data->team_names[0] = strdup("red");
        data->team_names[1] = strdup("blue");
        data->team_names[2] = NULL;
    }
    return data;
}
