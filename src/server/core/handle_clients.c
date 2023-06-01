/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_clients
*/

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include "implementation.h"

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
    if (FD_ISSET(data->clients[cli_index]->fd, &write_fd_set)) {
        write_to_selected_client(&(data->clients)[cli_index]);
    }
    if (FD_ISSET(data->clients[cli_index]->fd, &read_fd_set)) {
        read_selected_client(data);
    }
}

static void handle_clients(data_t *data, fd_set read_fd_set,
    fd_set write_fd_set)
{
    for (int i = 0; data->clients[i]; i++) {
        data->curr_cli_index = i;
        if (data->clients[i]->fd > 0 && data->clients[i]->player &&
        data->clients[i]->player->pending_cmd_queue[0])
            handle_pending_cmd(data);
        if (data->clients[i]->fd > 0)
            run_client_flow(data, i, read_fd_set, write_fd_set);
    }
}

int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data)
{
    fd_set read_fd_set;
    fd_set write_fd_set;
    struct timeval *timeout = NULL;

    timeout = get_next_timeout(data);
    get_fd_set(data->clients, &read_fd_set, &write_fd_set);
    FD_SET(server_fd, &read_fd_set);
    time(&data->last_select);
    select(FD_SETSIZE, &read_fd_set, &write_fd_set, NULL, timeout);
    free(timeout);
    if (!keep_running)
        return 1;
    if (FD_ISSET(server_fd, &read_fd_set)) {
        welcome_selected_client((struct sockaddr *) addr, server_fd,
        &(data->clients));
    }
    handle_clients(data, read_fd_set, write_fd_set);
    return 0;
}
