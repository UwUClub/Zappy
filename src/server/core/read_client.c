/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** read_client
*/

#include <errno.h>
#include <stdio.h>
#include "core.h"
#include "implementation.h"
#include "utils.h"

static void bufferize_cmd(client_t **client, char *cmd,
const unsigned int size)
{
    char *clean_cmd = NULL;

    clean_cmd = strdup(cmd);
    if (clean_cmd[size - 1] == '\n')
        clean_cmd[size - 1] = '\0';
    if (size > 1 && clean_cmd[size - 2] == '\r')
        clean_cmd[size - 2] = '\0';
    if ((*client)->input == NULL) {
        (*client)->input = strdup(clean_cmd);
    } else {
        (*client)->input = concat_str((*client)->input, clean_cmd);
    }
    free(clean_cmd);
}

void read_selected_client(data_t *data)
{
    char buffer[1024];
    ssize_t size = 0;
    client_t *cli = data->clients[data->curr_cli_index];

    size = read(cli->fd, buffer, 1024);
    if (size > 0 && buffer[0] != '\n') {
        buffer[size] = '\0';
        bufferize_cmd(&cli, buffer, (unsigned int) size);
        if (buffer[size - 1] != '\n')
            return;
        parse_input(data);
        free(cli->input);
        cli->input = NULL;
    } else if (size == 0) {
        handle_client_quit(data);
    }
}
