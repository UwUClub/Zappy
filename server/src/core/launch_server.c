/*
** EPITECH PROJECT, 2023
** zappy_server
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

static map_t *init_map(const unsigned int width, const unsigned int height)
{
    map_t *map = malloc(sizeof(map_t));

    map->width = width;
    map->height = height;
    map->tiles = NULL;
    return map;
}

data_t *init_data()
{
    data_t *data = malloc(sizeof(data_t));

    data->curr_cli_index = -1;
    data->clients = init_clients();
    data->map = init_map(10, 10);
    data->team_names = malloc(sizeof(char *) * 3);
    data->team_names[0] = strdup("red");
    data->team_names[1] = strdup("blue");
    data->team_names[2] = NULL;
    data->cli_per_team = 3;
    data->freq = 7;
    return data;
}

void free_data(data_t *data)
{
    close_clients(data->clients);
    free(data->map);
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
    if (listen(server_fd, MAX_CONNECTIONS) < 0)
        return 84;
    printf("Port : %i\n", port);
    listen_to_inputs(&my_addr, server_fd, data);
    close(server_fd);
    return 0;
}
