/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_single_client
*/

#include <errno.h>
#include "server_core.h"

void welcome_selected_client(struct sockaddr *addr, int server_fd,
client_t **clients)
{
    socklen_t addrlen = sizeof(*addr);
    int client_fd = 0;

    client_fd = accept(server_fd, addr, &addrlen);
    if (client_fd < 0) {
        fprintf(stderr, "Accept failed [%s]\n", strerror(errno));
    }
    for (int id = 0; clients[id]; id++) {
        if (clients[id]->fd < 0) {
            clients[id]->fd = client_fd;
            send_to_client(clients, id, "WELCOME\n");
            break;
        }
    }
}
