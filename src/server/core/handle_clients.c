/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_clients
*/

#include <errno.h>
#include <signal.h>
#include <string.h>
#include "server_implementation.h"

static int keep_running = 1;

void detect_ctrl_c(int dummy)
{
    keep_running = 0;
}

static void get_fd_set(client_t **clients, fd_set *read_fd_set,
    fd_set *write_fd_set)
{
    FD_ZERO(read_fd_set);
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd >= 0) {
            FD_SET(clients[i]->fd, read_fd_set);
        }
    }
    FD_ZERO(write_fd_set);
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd >= 0 && strlen(clients[i]->output) > 0) {
            FD_SET(clients[i]->fd, write_fd_set);
        }
    }
}

static void run_client_flow(data_t *data, const int cli_index,
    fd_set read_fd_set, fd_set write_fd_set)
{
    if (data->clients[cli_index]->fd > 0 &&
        FD_ISSET(data->clients[cli_index]->fd, &write_fd_set)) {
        write_to_selected_client(&(data->clients)[cli_index]);
    }
    if (data->clients[cli_index]->fd > 0 &&
        FD_ISSET(data->clients[cli_index]->fd, &read_fd_set)) {
        data->curr_cli_index = cli_index;
        read_selected_client(data);
    }
}

int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data)
{
    fd_set read_fd_set;
    fd_set write_fd_set;

    get_fd_set(data->clients, &read_fd_set, &write_fd_set);
    FD_SET(server_fd, &read_fd_set);
    select(FD_SETSIZE, &read_fd_set, &write_fd_set, NULL, NULL);
    if (!keep_running) {
        return 1;
    }
    if (FD_ISSET(server_fd, &read_fd_set)) {
        welcome_selected_client((struct sockaddr *) addr, server_fd,
        &(data->clients));
    }
    for (int i = 0; data->clients[i]; i++) {
        run_client_flow(data, i, read_fd_set, write_fd_set);
    }
    return 0;
}
