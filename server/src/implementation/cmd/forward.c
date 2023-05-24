/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** forward
*/

#include <stdio.h>
#include "server_implementation.h"

int forward(data_t *data, char **args)
{
    printf("forward\n");
    if (args) {
        for (int i = 0; args[i]; i++) {
            printf(" - %s\n", args[i]);
        }
    }
    return 0;
}
