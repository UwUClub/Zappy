/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** option_setters
*/

#include <stdio.h>
#include "core.h"
#include "utils.h"

int set_port(data_t *data, char *value)
{
    data->port = atoi(value);
    return 0;
}

int set_team_names(data_t *data, char *value)
{
    data->team_names = str_to_word_array(value, " ");
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
    data->cli_per_team = atoi(value);
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
