/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_SERVER_IMPLEMENTATION_H
    #define ZAPPY_SERVER_IMPLEMENTATION_H

    #include "server_core.h"

    typedef struct cmd_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } cmd_t;

    int parse_input(data_t *data);
    char *get_remaining_slots(data_t *data, char *team_name);
    int msz(data_t *data, char **args);
    char *get_world_dimensions(data_t *data);
    int forward(data_t *data, char **args);

#endif /* ZAPPY_SERVER_IMPLEMENTATION_H */
