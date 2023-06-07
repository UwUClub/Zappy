/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** init_server_data
*/

#include "core.h"
#include "default_values.h"
#include "server_data.h"
#include "server_options.h"
#include "utils.h"

static void set_data_default_values(data_t *data)
{
    data->curr_cli_index = -1;
    data->clients = NULL;
    data->map = malloc(sizeof(map_t));
    data->map->width = DEFAULT_MAP_WIDTH;
    data->map->height = DEFAULT_MAP_HEIGHT;
    data->map->tiles = NULL;
    data->teams = NULL;
    data->ip = DEFAULT_IP_ADDRESS;
    data->freq = DEFAULT_FREQ;
    data->port = DEFAULT_PORT;
    data->last_select_ms = 0;
    data->remaining_rsrc_spawn_ms = 0;
    data->nb_slots = 0;
}

static saved_opt_t *get_default_saved_opt(void)
{
    saved_opt_t *saved = NULL;

    saved = malloc(sizeof(saved_opt_t));
    saved->nb_cli_per_team = DEFAULT_CLI_PER_TEAM;
    saved->team_names = malloc(sizeof(char *) * (MAX_TEAMS + 1));
    for (int i = 0; i < MAX_TEAMS; i++) {
        asprintf(&saved->team_names[i], "%s%d", DEFAULT_TEAM_NAME, i + 1);
    }
    saved->team_names[MAX_TEAMS] = NULL;
    return saved;
}

data_t *init_server_data(int ac, char **av)
{
    data_t *data = NULL;
    saved_opt_t *saved = NULL;

    data = malloc(sizeof(data_t));
    saved = get_default_saved_opt();
    set_data_default_values(data);
    if (parse_data_options(data, saved, ac, av))
        return NULL;
    data->clients = malloc(sizeof(client_t *));
    data->clients[0] = NULL;
    init_map_tiles(data);
    init_teams(data, saved->team_names, saved->nb_cli_per_team);
    free_word_array(saved->team_names);
    free(saved);
    return data;
}
