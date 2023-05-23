/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** Header for server network
*/

#ifndef MYTEAMS_SERVER_CORE_H
    #define MYTEAMS_SERVER_CORE_H

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

    typedef struct client_s {
        int fd;
        char *username;
        char *uuid;
        char *input;
        char *output;
        char *team_uuid;
        char *channel_uuid;
        char *thread_uuid;
    } client_t;

    typedef struct data_s {
        int current_client_index;
        client_t **clients;
    } data_t;

    typedef struct instruction_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } instruction_t;

    int launch_server(unsigned int port);
    void init_single_client(client_t **client);
    void close_single_client(client_t *client);
    client_t **init_clients(void);
    void close_clients(client_t **clients);
    void select_clients(struct sockaddr_in *addr, int server_fd, data_t *data);
    void add_output(client_t **client, const char *msg);
    void broadcast_uuid(client_t **clients, const char *uuid, const char *msg);
    void broadcast_everyone(client_t **clients, const char *msg);
    void welcome_selected_client(struct sockaddr *addr, int server_fd,
    client_t **clients);
    void read_selected_client(data_t *data);
    void write_to_selected_client(client_t **client);
    client_t **get_clients_by_uuid(client_t **clients, char *uuid);

#endif /* MYTEAMS_SERVER_CORE_H */
