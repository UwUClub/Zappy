/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** parse_options
*/

#include <unistd.h>
#include <stdio.h>
#include "server_core.h"

static void print_help(__attribute__((unused)) data_t *data,
    __attribute__((unused)) char *value) {
    printf("help\n");
}

static void set_port(data_t *data, char *value) {
    data->port = atoi(value);
}

static const option_t options[] = {
    { 'h', &print_help },
    { 'p', &set_port },
    { 'x', &set_map_width },
    { 'y', &set_map_height },
    { 'n', &set_team_names },
    { 'c', &set_cli_per_team },
    { 'f', &set_freq },
    { -1, NULL }
};

static int parse_data_options(data_t *data, int ac, char **av)
{
    int option = 0;

    while (option != -1) {
        option = getopt(ac, av, "h:p:x:y:n:c:f");
        for (int i = 0; options[i].flag != -1; i++) {
            if (options[i].flag == optopt)
                options[i].func(data, optarg);
        }
        if (optopt == 'h')
            return 1;
    }
    return 0;
}

data_t *init_data(int ac, char **av)
{
    data_t *data = NULL;
    
    data = malloc(sizeof(data_t));
    data->curr_cli_index = -1;
    data->map_width = 10;
    data->map_height = 10;
    data->cli_per_team = 2;
    data->freq = 7;
    if (parse_data_options(data, ac, av))
        return NULL;
    if (!data->clients) {
        data->clients = init_clients(MAX_TEAMS * data->cli_per_team);
    }
    if (!data->team_names) {
        data->team_names = malloc(sizeof(char *) * 3);
        data->team_names[0] = strdup("red");
        data->team_names[1] = strdup("blue");
        data->team_names[2] = NULL;
    }
    return data;
}
