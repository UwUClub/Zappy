/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server network
*/

#ifndef ZAPPY_SERVER_CORE_H
    #define ZAPPY_SERVER_CORE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #define MAX_CONNECTIONS 1000

    typedef enum orientation_e {
        UNKNOWN = 0,
        NORTH,
        EAST,
        SOUTH,
        WEST
    } orientation_t;

    typedef struct client_s {
        int fd;
        int pos_x;
        int pos_y;
        orientation_t orientation;
        int level;
        int inventory[7];
        char *team_name;
        char *input;
        char *output;
    } client_t;

    typedef struct map_s {
        int width;
        int height;
        int **tiles;
    } map_t;

    typedef struct data_s {
        int curr_cli_index;
        client_t **clients;
        map_t *map;
        char **team_names;
        int cli_per_team;
        int freq;
    } data_t;

    typedef struct instruction_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } instruction_t;

    data_t *init_data();
    void free_data(data_t *data);
    int launch_server(unsigned int port, data_t *data);
    void init_single_client(client_t **client);
    void close_single_client(client_t *client);
    client_t **init_clients(void);
    void close_clients(client_t **clients);
    void select_clients(struct sockaddr_in *addr, int server_fd, data_t *data);
    void send_to_client(client_t **clients, const int id, const char *msg);
    void send_to_everyone(client_t **clients, const char *msg);
    void welcome_selected_client(struct sockaddr *addr, int server_fd,
    client_t **clients);
    void read_selected_client(data_t *data);
    void write_to_selected_client(client_t **client);

#endif /* ZAPPY_SERVER_CORE_H */
