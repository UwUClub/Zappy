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

static int keepRunning = 1;

void intHandler(int dummy)
{
    keepRunning = 0;
}

client_t **init_clients(const unsigned int max_connections)
{
    client_t **clients = NULL;
    unsigned int i = 0;

    clients = malloc(sizeof(client_t *) * (max_connections + 1));
    for (i = 0; i < max_connections; i++) {
        clients[i] = malloc(sizeof(client_t));
        init_single_client(&clients[i]);
    }
    clients[i] = NULL;
    return clients;
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

int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data)
{
    fd_set read_fd_set;
    fd_set write_fd_set;

    get_fd_set(data->clients, &read_fd_set, &write_fd_set);
    FD_SET(server_fd, &read_fd_set);
    select(FD_SETSIZE, &read_fd_set, &write_fd_set, NULL, NULL);
    if (!keepRunning)
        return 1;
    if (FD_ISSET(server_fd, &read_fd_set))
        welcome_selected_client((struct sockaddr *) addr, server_fd,
            data->clients);
    for (int i = 0; data->clients[i]; i++) {
        if (data->clients[i]->fd > 0 &&
            FD_ISSET(data->clients[i]->fd, &write_fd_set)) {
            write_to_selected_client(&(data->clients)[i]);
        }
        if (data->clients[i]->fd > 0 &&
            FD_ISSET(data->clients[i]->fd, &read_fd_set)) {
            data->curr_cli_index = i;
            read_selected_client(data);
        }
    }
    return 0;
}

void close_clients(client_t **clients)
{
    for (int i = 0; clients[i]; i++) {
        close_single_client(clients[i]);
        free(clients[i]);
    }
    free(clients);
}
