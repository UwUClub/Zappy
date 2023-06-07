/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** fork
*/

#include "implementation.h"
#include "player_cmd.h"
#include "gui_cmd.h"

static void append_egg(data_t *data, const unsigned int team_id,
    const int pos_x, const int pos_y)
{
    int nb_eggs = 0;

    for (int i = 0; data->teams[team_id]->eggs[i]; i++) {
        nb_eggs++;
    }
    data->teams[team_id]->nb_cli++;
    data->teams[team_id]->eggs = realloc(data->teams[team_id]->eggs,
        sizeof(egg_t *) * (nb_eggs + 2));
    data->teams[team_id]->eggs[nb_eggs] = malloc(sizeof(egg_t));
    data->teams[team_id]->eggs[nb_eggs]->id = data->teams[team_id]->nb_cli;
    data->teams[team_id]->eggs[nb_eggs]->progenitor_id = data->curr_cli_index;
    data->teams[team_id]->eggs[nb_eggs]->pos = malloc(sizeof(pos_t));
    data->teams[team_id]->eggs[nb_eggs]->pos->x = pos_x;
    data->teams[team_id]->eggs[nb_eggs]->pos->y = pos_y;
    data->teams[team_id]->eggs[nb_eggs + 1] = NULL;
    do_enw(data, data->teams[team_id]->eggs[nb_eggs]);
}

static int fork_cmd(data_t *data, __attribute__((unused)) char **args)
{
    pos_t *player_pos = data->clients[data->curr_cli_index]->player->pos;
    char *team_name = data->clients[data->curr_cli_index]->player->team_name;

    for (int i = 0; data->teams[i]; i++) {
        if (!strcmp(team_name, data->teams[i]->name)) {
            do_pfk(data, data->curr_cli_index);
            append_egg(data, i, player_pos->x, player_pos->y);
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return 0;
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return 1;
}

int schedule_fork(data_t *data, char **args)
{
    if (args != NULL) {
        return 1;
    }
    append_scheduler_to_queue(data, &fork_cmd, args, FORK_DELAY);
    return 0;
}
