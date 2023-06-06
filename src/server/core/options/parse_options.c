/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** parse_options
*/

#include "core.h"
#include "utils.h"
#include "server_options.h"

static const option_t options[] = {
    { 'h', &print_help },
    { 'p', &set_port },
    { 'x', &set_map_width },
    { 'y', &set_map_height },
    { 'c', &set_cli_per_team },
    { 'f', &set_freq },
    { 'v', &set_ip },
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
    set_team_names(data, teams);
    free(teams);
}

static int parse_single_option(int option, data_t *data, int ac,
    char **av)
{
    int status = 0;

    for (int i = 0; options[i].flag != -1; i++) {
        if (options[i].flag == option)
            status = options[i].func(data, optarg);
        if (status == 84)
            return 1;
    }
    return option == 'h';
}

int parse_data_options(data_t *data, int ac, char **av)
{
    int option = 0;

    while (option != -1) {
        option = getopt(ac, av, "hp:x:y:n:c:f:v:");
        if (option == 'n')
            parse_team_names(data, ac, av);
        if (parse_single_option(option, data, ac, av))
            return 1;
    }
    return 0;
}
