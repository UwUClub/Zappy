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

static int parse_cmd(data_t *data)
{
    char *cmd_name = NULL;
    char **args = NULL;
    int status = -1;
    client_t *client = data->clients[data->curr_cli_index];

    cmd_name = strtok(strdup(client->input), " ");
    if (strlen(client->input) > strlen(cmd_name))
        args = str_to_word_array(client->input + strlen(cmd_name) + 1, " ");
    for (int i = 0; commands[i].name != NULL; i++)
        if (!strcmp(cmd_name, commands[i].name))
            status = commands[i].func(data, args); 
    if (status == -1)
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
    free(cmd_name);
    free_word_array(args);
    return status;
}

int parse_input(data_t *data)
{
    client_t *client = data->clients[data->curr_cli_index];

    if (!client->team_name) {
        return parse_team_name(data);
    }
    return parse_cmd(data);
}
