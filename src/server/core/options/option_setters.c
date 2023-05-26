/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** option_setters
*/

#include "server_core.h"
#include "utils.h"

void set_port(data_t *data, char *value) {
    data->port = atoi(value);
}

void set_map_width(data_t *data, char *value) {
    data->map_width = atoi(value);
}

void set_map_height(data_t *data, char *value) {
    data->map_height = atoi(value);
}

void set_team_names(data_t *data, char *value) {
    data->team_names = str_to_word_array(value, " ");
}

void set_cli_per_team(data_t *data, char *value) {
    data->cli_per_team = atoi(value);
    data->clients = init_clients(MAX_TEAMS * data->cli_per_team);
}

void set_freq(data_t *data, char *value) {
    data->freq = atoi(value);
}
