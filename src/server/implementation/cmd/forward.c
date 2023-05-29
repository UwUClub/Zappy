/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** forward
*/

#include <stdio.h>
#include "server_implementation.h"

int forward(data_t *aData, __attribute__ ((unused)) char **aArgs)
{
    char *myMsg = strdup("ok");

    if (aData->clients[aData->curr_cli_index]->orientation == NORTH)
        aData->clients[aData->curr_cli_index]->pos_y -= 1;
    else if (aData->clients[aData->curr_cli_index]->orientation == SOUTH)
        aData->clients[aData->curr_cli_index]->pos_y += 1;
    else if (aData->clients[aData->curr_cli_index]->orientation == EAST)
        aData->clients[aData->curr_cli_index]->pos_x += 1;
    else if (aData->clients[aData->curr_cli_index]->orientation == WEST)
        aData->clients[aData->curr_cli_index]->pos_x -= 1;
    send_to_client(aData->clients, aData->curr_cli_index, myMsg);
    free(myMsg);
    return 0;
}
