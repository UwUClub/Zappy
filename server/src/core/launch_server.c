/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** launch_server
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server_core.h"
#include "server_implementation.h"
#include "utils.h"

data_t *init_data(void)
{
    data_t *data = malloc(sizeof(data_t));

    data->current_client_index = -1;
    data->clients = init_clients();
    return data;
}

void free_data(data_t *data)
{
    close_clients(data->clients);
    printf("@free teams\n");
    free(data);
}

static void listen_to_inputs(struct sockaddr_in *addr, int server_fd)
{
    data_t *data = NULL;

    data = init_data();
    while (1) {
        select_clients(addr, server_fd, data);
    }
    free_data(data);
}

int launch_server(unsigned int port)
{
    int server_fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in my_addr = get_sockaddr(inet_addr("127.0.0.1"), port);

    if (server_fd < 0)
        return 84;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int) { 1 }, sizeof(int));
    if (bind(server_fd, (const struct sockaddr *) &my_addr,
    sizeof(struct sockaddr_in)) < 0)
        return 84;
    if (listen(server_fd, MAX_CONNECTIONS) < 0)
        return 84;
    init_save_dirs();
    printf("Listening on port %i...\n", port);
    listen_to_inputs(&my_addr, server_fd);
    close(server_fd);
    return 0;
}
