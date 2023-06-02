/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** main
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "utils.h"

int main(int ac, char **av)
{
    time_t t = 0;
    data_t *data = NULL;

    signal(SIGINT, detect_ctrl_c);
    srand((unsigned) time(&t));
    data = init_server_data(ac, av);
    if (!data)
        return 84;
    launch_server(data);
    free_server_data(data);
    return 0;
}
