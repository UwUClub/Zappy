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
    return SUCCESS_STATUS;
}

int set_freq(data_t *data, char *value)
{
    if (!value || !is_int(value) || atoi(value) < MIN_FREQ
    || atoi(value) > MAX_FREQ) {
        dprintf(2, "\n-f option only accepts integer values between ");
        dprintf(2, "%i and %i\n", MIN_FREQ, MAX_FREQ);
        print_help(data, NULL);
        return ERROR_STATUS;
    }
    data->freq = atoi(value);
    return SUCCESS_STATUS;
}

int set_ip(data_t *data, char *value)
{
    if (!value || !is_ip(value)) {
        dprintf(2, "\n-v option only accepts valid IPv4 addresses\n");
        print_help(data, NULL);
        return ERROR_STATUS;
    }
    data->ip = strdup(value);
    return SUCCESS_STATUS;
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
