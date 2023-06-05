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
    init_single_client(&cli);
}
