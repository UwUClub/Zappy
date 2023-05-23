/*
** EPITECH PROJECT, 2023
** my_teams
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
    printf("Accepted a new connection with fd: %d\n", client_fd);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (clients[i]->fd < 0) {
            clients[i]->fd = client_fd;
            break;
        }
    }
}
