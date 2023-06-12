/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_client_quit
*/

#include "core.h"

static void send_pdi(data_t *data)
{
    char *msg = NULL;

    asprintf(&msg, "pdi %d\n", data->curr_cli_index);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

void handle_client_quit(data_t *data)
{
    client_t *cli = data->clients[data->curr_cli_index];
    char *msg = NULL;

    if (cli->player != NULL) {
        send_pdi(data);
    }
    close_single_client(cli);
    free(cli);
    for (int i = data->curr_cli_index; data->clients[i]; i++) {
        data->clients[i] = data->clients[i + 1];
    }
    data->nb_clients--;
    data->curr_cli_index--;
}
