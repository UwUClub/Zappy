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

static void append_client(client_t ***clients, int client_fd)
{
    int nb_clients = 0;

    for (int id = 0; (*clients)[id]; id++)
        nb_clients++;
    *clients = (client_t **) realloc(*clients, sizeof(client_t *) *
    (nb_clients + 2));
    (*clients)[nb_clients] = malloc(sizeof(client_t));
    init_single_client(&((*clients)[nb_clients]));
    (*clients)[nb_clients]->fd = client_fd;
    (*clients)[nb_clients + 1] = NULL;
    send_to_client(*clients, nb_clients, "WELCOME\n");
}

void welcome_selected_client(struct sockaddr *addr, int server_fd,
client_t ***clients)
{
    socklen_t addrlen = sizeof(*addr);
    int client_fd = 0;
    int nb_clients = 0;

    client_fd = accept(server_fd, addr, &addrlen);
    if (client_fd < 0) {
        fprintf(stderr, "Accept failed [%s]\n", strerror(errno));
    }
    append_client(clients, client_fd);
}
