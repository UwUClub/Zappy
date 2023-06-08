/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** parse_options
*/

#include <unistd.h>
#include "core.h"
#include "utils.h"
#include "server_options.h"

static void parse_team_names(data_t *data, saved_opt_t *saved,
    int ac, char **av)
{
    int length = 0;

    free_word_array(saved->team_names);
    saved->team_names = malloc(sizeof(char *) * (ac + 1));
    optind--;
    for (; optind < ac && *av[optind] != '-'; optind++) {
        saved->team_names[length] = strdup(av[optind]);
        length++;
    }
    saved->team_names[length] = NULL;
}

int parse_cli_per_team(data_t *data, saved_opt_t *saved,
    char *value)
{
    if (!value || !is_int(value) || atoi(value) < 1) {
        dprintf(2, "\n-c option only accepts integer values ");
        dprintf(2, "greater or equal to 1\n");
        print_help(data, NULL);
        return 84;
    }
    saved->nb_cli_per_team = atoi(value);
    return 0;
}

static int parse_single_option(int option, data_t *data, int ac, char **av)
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

int parse_data_options(data_t *data, saved_opt_t *saved, int ac, char **av)
{
    int option = 0;

    while (option != -1) {
        option = getopt(ac, av, "hp:x:y:n:c:f:v:");
        if (option == 'n') {
            parse_team_names(data, saved, ac, av);
        }
        if (option == 'c') {
            parse_cli_per_team(data, saved, optarg);
        }
        if (parse_single_option(option, data, ac, av)) {
            return 1;
        }
    }
    return 0;
}
