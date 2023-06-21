/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** inventory
*/

#include "core.h"
#include "implementation.h"
#include "player_cmd.h"

static int get_inventory(data_t *data, __attribute__((unused)) char **args)
{
    char *inventory = NULL;
    int value = 0;

    value = asprintf(&inventory, "[ food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
        data->clients[data->curr_cli_index]->player->inventory[0],
        data->clients[data->curr_cli_index]->player->inventory[1],
        data->clients[data->curr_cli_index]->player->inventory[2],
        data->clients[data->curr_cli_index]->player->inventory[3],
        data->clients[data->curr_cli_index]->player->inventory[4],
        data->clients[data->curr_cli_index]->player->inventory[5],
        data->clients[data->curr_cli_index]->player->inventory[6]);
    if (value == -1)
        return ERROR_STATUS;
    send_to_client(data->clients, data->curr_cli_index, inventory);
    free(inventory);
    return SUCCESS_STATUS;
}

int schedule_inventory(data_t *data, char **args)
{
    if (args != NULL) {
        return ERROR_STATUS;
    }
    append_scheduler_to_queue(data, &get_inventory, args, INVENTORY_DELAY);
    return SUCCESS_STATUS;
}
