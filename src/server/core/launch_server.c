/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** launch_server
*/

#include <unistd.h>
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

void free_data(data_t *data)
{
    close_clients(data->clients);
    free_word_array(data->team_names);
    free(data);
}

static void listen_to_inputs(struct sockaddr_in *addr, int server_fd,
    data_t *data)
{
    while (1) {
        select_clients(addr, server_fd, data);
    }
}

int launch_server(unsigned int port, data_t *data)
{
    int server_fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in my_addr = get_sockaddr(inet_addr("127.0.0.1"), port);

    if (server_fd < 0)
        return 84;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int) { 1 }, sizeof(int));
    if (bind(server_fd, (const struct sockaddr *) &my_addr,
    sizeof(struct sockaddr_in)) < 0)
        return 84;
    if (listen(server_fd, MAX_TEAMS * data->cli_per_team) < 0)
        return 84;
    printf("Port : %i\n", port);
    listen_to_inputs(&my_addr, server_fd, data);
    close(server_fd);
    return 0;
}
