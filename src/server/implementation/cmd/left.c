/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** left
*/

#include <stdio.h>
#include "server_implementation.h"

int left(data_t *aData, __attribute__ ((unused)) char **aArgs)
{
    char *myMsg = strdup("ok");

    if (aData->clients[aData->curr_cli_index]->orientation == NORTH)
        aData->clients[aData->curr_cli_index]->orientation = WEST;
    else if (aData->clients[aData->curr_cli_index]->orientation == SOUTH)
        aData->clients[aData->curr_cli_index]->orientation = EAST;
    else if (aData->clients[aData->curr_cli_index]->orientation == EAST)
        aData->clients[aData->curr_cli_index]->orientation = NORTH;
    else if (aData->clients[aData->curr_cli_index]->orientation == WEST)
        aData->clients[aData->curr_cli_index]->orientation = SOUTH;
    send_to_client(aData->clients, aData->curr_cli_index, myMsg);
    free(myMsg);
    return 0;
}

