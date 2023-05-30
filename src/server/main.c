/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** main
*/

#include <stdio.h>
#include <signal.h>
#include "server_core.h"
#include "utils.h"

int main(int ac, char **av)
{
    data_t *data = NULL;

    signal(SIGINT, intHandler);
    data = init_data(ac, av);
    if (data) {
        launch_server(data);
        free_data(data);
    }
    return 0;
}
