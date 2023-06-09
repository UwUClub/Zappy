/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz
*/

#include "implementation.h"
#include "utils.h"

static void concat_str_item(char **result, const int item_quantity)
{
    char *str_item_quantity = NULL;

    str_item_quantity = int_to_s(item_quantity);
    *result = concat_str(*result, " ");
    *result = concat_str(*result, str_item_quantity);
    free(str_item_quantity);
}

static char *get_tile_at(data_t *data, const int x, const int y)
{
    int *tile = data->map->tiles[x][y];
    char *result = NULL;

    result = strdup("");
    for (int i = 0; i < TILE_SIZE; i++) {
        concat_str_item(&result, tile[i]);
    }
    return result;
}

static int parse_args(data_t *data, char **args, int *x, int *y)
{
    if (!args || word_array_len(args) != 2 || !is_int(args[0]) ||
    !is_int(args[1]))
        return 84;
    *x = atoi(args[0]);
    *y = atoi(args[1]);
    if (*x < 0 || *x >= data->map->width || *y < 0 || *y >= data->map->height)
        return 84;
    return 0;
}

int do_bct_to_all_gui(data_t *data, const int x, const int y)
{
    char *msg = NULL;
    char *resources = NULL;

    resources = get_tile_at(data, x, y);
    asprintf(&msg, "bct %d %d%s\n", x, y, resources);
    send_to_all_gui(data->clients, msg);
    free(resources);
    free(msg);
    return 0;
}

int do_bct(data_t *data, char **args)
{
    char *msg = NULL;
    char *resources = NULL;
    int x = 0;
    int y = 0;

    if (parse_args(data, args, &x, &y) == 84)
        return 1;
    resources = get_tile_at(data, x, y);
    asprintf(&msg, "bct %d %d%s\n", x, y, resources);
    send_to_client(data->clients, data->curr_cli_index, msg);
    free(resources);
    free(msg);
    return 0;
}
