/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** player_actions.c
*/

#include "implementation.h"
#include "gui_cmd.h"
#include "player_cmd.h"

void set_players_freeze_state(client_t **clients, pos_t *pos,
    const int target_lvl, const int new_state)
{
    for (int i = 0; clients[i]; i++) {
        if (is_player_valid_for_incantation(clients, i, pos, target_lvl)) {
            clients[i]->player->is_freezed = new_state;
        }
    }
}

void increment_players_level(data_t *data, pos_t *pos,
    const int target_lvl)
{
    char *msg = NULL;

    for (int i = 0; data->clients[i]; i++) {
        if (is_player_valid_for_incantation(data->clients, i, pos,
        target_lvl)) {
            data->clients[i]->player->level = target_lvl;
            send_plv_to_all_gui(data, data->clients[i]->player);
            asprintf(&msg, "Current level: %d\n", target_lvl);
            send_to_client(data->clients, i, msg);
            free(msg);
        }
    }
}

void send_ko_to_players(client_t **clients, pos_t *pos, const int target_lvl)
{
    for (int i = 0; clients[i]; i++) {
        if (is_player_valid_for_incantation(clients, i, pos,
        target_lvl)) {
            send_to_client(clients, i, "ko\n");
        }
    }
}

void send_ko_to_players_except_current(data_t *data, pos_t *pos,
    const int target_lvl)
{
    for (int i = 0; data->clients[i]; i++) {
        if (is_player_valid_for_incantation(data->clients, i, pos,
        target_lvl) && i != data->curr_cli_index) {
            send_to_client(data->clients, i, "ko\n");
        }
    }
}
