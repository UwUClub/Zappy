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

    int parse_cmd(data_t *data);
    int msz(data_t *data, char **args);
    int forward(data_t *data, char **args);

#endif /* ZAPPY_SERVER_IMPLEMENTATION_H */
