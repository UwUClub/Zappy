/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** main
*/

#include <stdio.h>
#include "server_core.h"
#include "utils.h"

int main(int ac, char **av)
{
    data_t *data = NULL;

    data = init_server_data(ac, av);
    if (data) {
        launch_server(data);
        free_server_data(data);
    }
    return 0;
}
