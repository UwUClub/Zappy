/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** inventory
*/

#include "server_implementation.h"
#include <stdio.h>


int inventory(data_t *data, char **args)
{
    char *inventory = NULL;
    int value = 0;

    if (args != NULL)
        return 1;
    value = asprintf(&inventory, "[food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        data->clients[data->curr_cli_index]->inventory[0],
        data->clients[data->curr_cli_index]->inventory[1],
        data->clients[data->curr_cli_index]->inventory[2],
        data->clients[data->curr_cli_index]->inventory[3],
        data->clients[data->curr_cli_index]->inventory[4],
        data->clients[data->curr_cli_index]->inventory[5],
        data->clients[data->curr_cli_index]->inventory[6]);
    if (value == -1)
        return 1;
    send_to_client(data->clients, data->curr_cli_index, inventory);
    free(inventory);
    return 0;
}
