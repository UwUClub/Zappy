/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz
*/

#include <stdio.h>
#include "server_implementation.h"
#include "utils.h"

static void concat_str_item(char **result, const int item_quantity)
{
    char *str_item_quantity = NULL;

    str_item_quantity = inttos(item_quantity);
    *result = concat_str(*result, " ");
    *result = concat_str(*result, str_item_quantity);
}

static char *get_tile_at(data_t *data, const int x, const int y)
{
    item_packet_t *tile = data->map_tiles[y][x];
    char *result = NULL;

    result = strdup("");
    concat_str_item(&result, tile->food);
    concat_str_item(&result, tile->linemate);
    concat_str_item(&result, tile->deraumere);
    concat_str_item(&result, tile->sibur);
    concat_str_item(&result, tile->mendiane);
    concat_str_item(&result, tile->phiras);
    concat_str_item(&result, tile->thystame);
    result = concat_str(result, "\n");
    return result;
}

int bct(data_t *data, char **args)
{
    char *msg = NULL;
    char *result = NULL;
    int x = 0;
    int y = 0;

    if (!args || word_array_len(args) != 2 || !is_int(args[0]) ||
    !is_int(args[1]))
        return 1;
    x = atoi(args[0]);
    y = atoi(args[1]);
    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
        return 1;
    msg = strdup("bct");
    result = get_tile_at(data, atoi(args[0]), atoi(args[1]));
    msg = concat_str(msg, result);
    free(result);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(msg);
    return 0;
}
