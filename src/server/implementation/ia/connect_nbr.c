/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** connect_nbr
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

int connect_nbr(data_t *data, char **args)
{
    int nb = 0;
    char *msg = NULL;

    if (args != NULL) {
        return 1;
    }
    nb = get_remaining_slots(data,
    data->clients[data->curr_cli_index]->team_name);
    msg = int_to_s(nb);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}
