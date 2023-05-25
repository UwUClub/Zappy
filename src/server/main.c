/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** main
*/

#include <stdio.h>
#include "server_core.h"
#include "utils.h"

static void print_help(void)
{
    printf("USAGE: ./zappy_server ...\n\n");
}

int main(int ac, char **av)
{
    data_t *data = NULL;

    if (ac >= 2 && (!strcmp(av[1], "-help") || !strcmp(av[1], "-h"))) {
        print_help();
        return 0;
    }
    data = init_data();
    launch_server(4242, data);
    free_data(data);
    return 0;
}
