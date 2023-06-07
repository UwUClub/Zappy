/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** append_player_client
*/

#include "core.h"
#include "implementation.h"
#include "server_data.h"
#include "utils.h"
#include "gui_cmd.h"
#include "player_cmd.h"

static void send_welcome_data(data_t *data, const int remaining_slots)
{
    char *str_remaining_slots = NULL;
    char *world_dimensions = NULL;

    str_remaining_slots = int_to_s(remaining_slots - 1);
    str_remaining_slots = concat_str(str_remaining_slots, "\n");
    world_dimensions = get_world_dimensions(data);
    send_to_client(data->clients, data->curr_cli_index, str_remaining_slots);
    send_to_client(data->clients, data->curr_cli_index, world_dimensions);
    free(str_remaining_slots);
    free(world_dimensions);
}

static void hatch_egg(data_t *data, char *team_name)
{
    int team_index = 0;
    int egg_index = 0;
    egg_t *egg = NULL;

    team_index = get_team_index_by_name(data->teams, team_name);
    egg_index = rand() % get_nb_eggs(data, team_name);
    egg = data->teams[team_index]->eggs[egg_index];
    data->clients[data->curr_cli_index]->player->id = egg->id;
    data->clients[data->curr_cli_index]->player->pos->x = egg->pos->x;
    data->clients[data->curr_cli_index]->player->pos->y = egg->pos->y;
    free_egg(data->teams[team_index]->eggs[egg_index]);
    for (int i = egg_index; data->teams[team_index]->eggs[i]; i++) {
        data->teams[team_index]->eggs[i] = data->teams[team_index]->eggs[i + 1];
    }
}

int append_player_client(data_t *data, char *team_name)
{
    int remaining_slots = 0;

    remaining_slots = get_nb_eggs(data, team_name);
    if (remaining_slots <= 0) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 84;
    }
    init_player(&(data->clients[data->curr_cli_index]), team_name, data->map);
    hatch_egg(data, team_name);
    send_welcome_data(data, remaining_slots);
    do_ebo(data);
    do_pnw(data);
    data->clients[data->curr_cli_index]->is_registered = 1;
    return 0;
}
