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

static void run_enw_through_eggs(data_t *data)
{
    for (int i = 0; data->teams[i]; i++) {
        for (int j = 0; data->teams[i]->eggs[j]; j++) {
            send_enw_to_current_cli(data, data->teams[i]->eggs[j]);
        }
    }
}

static void run_pnw_pin_through_players(data_t *data)
{
    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data->clients, i)) {
            send_pnw_to_current_cli(data, data->clients[i]->player);
            send_pin_to_current_cli(data, data->clients[i]->player);
        }
    }
}

int append_gui_client(data_t *data)
{
    data->clients[data->curr_cli_index]->is_registered = 1;
    do_msz(data, NULL);
    do_sgt(data, NULL);
    do_mct(data, NULL);
    do_tna(data, NULL);
    run_enw_through_eggs(data);
    run_pnw_pin_through_players(data);
    return SUCCESS_STATUS;
}
