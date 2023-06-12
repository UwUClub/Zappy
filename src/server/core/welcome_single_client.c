/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_single_client
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "core.h"

static void append_client(data_t *data, int client_fd)
{
    data->clients = (client_t **) realloc(data->clients, sizeof(client_t *) *
    (data->nb_clients + 2));
    data->clients[data->nb_clients] = malloc(sizeof(client_t));
    init_single_client(&(data->clients)[data->nb_clients]);
    data->clients[data->nb_clients]->fd = client_fd;
    data->clients[data->nb_clients + 1] = NULL;
    send_to_client(data->clients, data->nb_clients, "WELCOME\n");
    data->nb_clients++;
}

void welcome_selected_client(struct sockaddr *addr, int server_fd,
data_t *data)
{
    socklen_t addrlen = sizeof(*addr);
    int client_fd = 0;
    int nb_clients = 0;

    client_fd = accept(server_fd, addr, &addrlen);
    if (client_fd < 0) {
        fprintf(stderr, "Accept failed [%s]\n", strerror(errno));
    }
    append_client(data, client_fd);
}
