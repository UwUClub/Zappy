/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** inventory
*/

#include "implementation.h"
#include "player_cmd.h"

int get_inventory(data_t *data, char **args)
{
    char *inventory = NULL;
    int value = 0;

    if (args != NULL)
        return 1;
    value = asprintf(&inventory, "[food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        data->clients[data->curr_cli_index]->player->inventory[0],
        data->clients[data->curr_cli_index]->player->inventory[1],
        data->clients[data->curr_cli_index]->player->inventory[2],
        data->clients[data->curr_cli_index]->player->inventory[3],
        data->clients[data->curr_cli_index]->player->inventory[4],
        data->clients[data->curr_cli_index]->player->inventory[5],
        data->clients[data->curr_cli_index]->player->inventory[6]);
    if (value == -1)
        return 1;
    send_to_client(data->clients, data->curr_cli_index, inventory);
    free(inventory);
    return 0;
}
