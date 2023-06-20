/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_client_quit
*/

#include "core.h"
#include "gui_cmd.h"

void handle_client_quit(data_t *data)
{
    client_t *cli = data->clients[data->curr_cli_index];
    char *msg = NULL;

    if (cli->player != NULL) {
        do_pdi(data, cli->player->id);
    }
    close_single_client(cli);
    free(cli);
    data->clients[data->curr_cli_index] = NULL;
    for (int i = data->curr_cli_index; data->clients[i]; i++) {
        data->clients[i] = data->clients[i + 1];
    }
    data->nb_clients--;
    data->curr_cli_index--;
}
