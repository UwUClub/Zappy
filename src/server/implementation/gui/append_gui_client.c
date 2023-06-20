/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** append_gui_client
*/

#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"
#include "player_cmd.h"

static void run_bct_through_map(data_t *data)
{
    char *x_str = NULL;
    char *y_str = NULL;

    for (int y = 0; y < data->map->height; y++) {
        for (int x = 0; x < data->map->width; x++) {
            x_str = int_to_s(x);
            y_str = int_to_s(y);
            do_bct(data, (char *[]){x_str, y_str, NULL});
            free(x_str);
            free(y_str);
        }
    }
}

static void run_enw_through_eggs(data_t *data)
{
    for (int i = 0; data->teams[i]; i++) {
        for (int j = 0; data->teams[i]->eggs[j]; j++) {
            do_enw(data, data->teams[i]->eggs[j]);
        }
    }
}

static void run_pnw_through_players(data_t *data)
{
    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data->clients, i)) {
            do_single_pnw(data, data->clients[i]->player);
        }
    }
}

int append_gui_client(data_t *data)
{
    data->clients[data->curr_cli_index]->is_registered = 1;
    do_msz(data, NULL);
    do_sgt(data, NULL);
    run_bct_through_map(data);
    do_tna(data, NULL);
    run_enw_through_eggs(data);
    run_pnw_through_players(data);
    return SUCCESS_STATUS;
}
