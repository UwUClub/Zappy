/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** main
*/

#include <stdio.h>
#include "server_core.h"
#include "utils.h"

static void print_help(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("\tport is the port number on which the server socket listens.\n");
}

int main(int ac, char **av)
{
    if (ac != 2) {
        print_help();
        return 84;
    }
    if (strcmp(av[1], "-help") == 0) {
        print_help();
        return 0;
    }
    if (!is_int(av[1])) {
        printf("Port must be an integer.\n");
        return 84;
    }
    launch_server(atoi(av[1]));
    return 0;
}
