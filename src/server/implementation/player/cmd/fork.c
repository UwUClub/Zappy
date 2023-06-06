/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** fork
*/

#include "implementation.h"
#include "player_cmd.h"

static void append_egg(data_t *data, const unsigned int team_index,
    const int pos_x, const int pos_y)
{
    int nb_eggs = 0;

    for (int i = 0; data->teams[team_index]->eggs[i]; i++) {
        nb_eggs++;
    }
    data->teams[team_index]->nb_cli++;
    data->teams[team_index]->eggs = realloc(data->teams[team_index]->eggs,
        sizeof(pos_t *) * (nb_eggs + 2));
    data->teams[team_index]->eggs[nb_eggs] = malloc(sizeof(pos_t));
    data->teams[team_index]->eggs[nb_eggs]->x = pos_x;
    data->teams[team_index]->eggs[nb_eggs]->y = pos_y;
    data->teams[team_index]->eggs[nb_eggs + 1] = NULL;
}

static int fork_cmd(data_t *data, __attribute__((unused)) char **args)
{
    pos_t *player_pos = data->clients[data->curr_cli_index]->player->pos;
    char *team_name = data->clients[data->curr_cli_index]->player->team_name;

    for (int i = 0; data->teams[i]; i++) {
        if (!strcmp(team_name, data->teams[i]->name)) {
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
