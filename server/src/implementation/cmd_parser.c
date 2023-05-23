/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** cmd_parser
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

static const cmd_t commands[] = {
    {"msz", &msz},
    {"Forward", &forward},
    {NULL, NULL}
};

int parse_cmd(data_t *data)
{
    char *cmd_name = NULL;
    char **args = NULL;
    int status = 0;
    client_t *client = data->clients[data->curr_cli_index];

    cmd_name = strtok(strdup(client->input), " ");
    if (strlen(client->input) > strlen(cmd_name))
        args = parse_quotes(client->input + strlen(cmd_name) + 1);
    for (int i = 0; commands[i].name != NULL; i++)
        if (strcmp(cmd_name, commands[i].name) == 0)
            status = commands[i].func(data, args);
    free(cmd_name);
    free_word_array(args);
    return status;
}
