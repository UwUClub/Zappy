/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** cmd_parser
*/

#include <stdlib.h>
#include <string.h>
#include "server_implementation.h"
#include "utils.h"

static const cmd_t player_commands[] = {
    {"Forward", &move_forward},
    {"Right", &move_right},
    {"Left", &move_left},
    {"Take", &take},
    {"Set", &set},
    {"Connect_nbr", &connect_nbr},
    {NULL, NULL}
};

static const cmd_t gui_commands[] = {
    {"msz", &do_msz},
    {"bct", &do_bct},
    {"sgt", &do_sgt},
    {NULL, NULL}
};

static void throw_unknown_cmd(data_t *data)
{
    char *team_name = data->clients[data->curr_cli_index]->team_name;

    if (!strcmp("GRAPHIC", team_name))
        send_to_client(data->clients, data->curr_cli_index, "suc\n");
    else
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
}

static int exec_cmd(data_t *data, int (*func)(data_t *data, char **args),
    char **args)
{
    char *team_name = data->clients[data->curr_cli_index]->team_name;
    int status = 0;

    status = func(data, args);
    if (status == 1 && !strcmp("GRAPHIC", team_name)) {
        send_to_client(data->clients, data->curr_cli_index, "sbp\n");
    }
    if (status == 1 && strcmp("GRAPHIC", team_name)) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
    }
    return status;
}

static int find_cmd(data_t *data, const cmd_t commands[], char *cmd_name,
    char **args)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (!strcmp(cmd_name, commands[i].name)) {
            return exec_cmd(data, commands[i].func, args);
        }
    }
    throw_unknown_cmd(data);
    return -1;
}

static int parse_cmd(data_t *data)
{
    char *cmd_name = NULL;
    char **args = NULL;
    int status = -1;
    client_t *client = data->clients[data->curr_cli_index];

    cmd_name = strtok(strdup(client->input), " ");
    if (strlen(client->input) > strlen(cmd_name))
        args = str_to_word_array(client->input + strlen(cmd_name) + 1, " ");
    if (!strcmp("GRAPHIC", client->team_name))
        status = find_cmd(data, gui_commands, cmd_name, args);
    else
        status = find_cmd(data, player_commands, cmd_name, args);
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
