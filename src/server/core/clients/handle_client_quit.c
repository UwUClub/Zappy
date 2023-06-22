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

    if (cli->player != NULL) {
        do_pdi(data, cli->player->id);
    }
    close_single_client(cli);
    free(cli);
    for (int i = data->curr_cli_index; i < data->nb_clients; i++) {
        data->clients[i] = data->clients[i + 1];
    }
    data->clients[data->nb_clients] = NULL;
    data->nb_clients--;
    data->curr_cli_index--;
}
