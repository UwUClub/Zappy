/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** input_parser
*/

#include "implementation.h"
#include "utils.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static int parse_team_name(data_t *data)
{
    if (!strcmp("GRAPHIC", data->clients[data->curr_cli_index]->input)) {
        data->clients[data->curr_cli_index]->is_registered = 1;
        return append_gui_client(data);
    }
    for (int i = 0; data->team_names[i]; i++) {
        if (!strcmp(data->team_names[i],
            data->clients[data->curr_cli_index]->input)) {
            data->clients[data->curr_cli_index]->is_registered = 1;
            return append_player_client(data, data->team_names[i]);
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return 0;
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
    if (client->is_registered && client->player)
        status = schedule_player_cmd(data, cmd_name, args);
    if (client->is_registered && !client->player)
        status = execute_gui_cmd(data, cmd_name, args);
    free(cmd_name);
    free_word_array(args);
    return status;
}

int parse_input(data_t *data)
{
    client_t *client = data->clients[data->curr_cli_index];

    if (!client->is_registered) {
        return parse_team_name(data);
    }
    return parse_cmd(data);
}
