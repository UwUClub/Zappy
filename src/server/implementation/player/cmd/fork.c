/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** fork
*/

#include "implementation.h"
#include "player_cmd.h"
#include "gui_cmd.h"
#include "server_data.h"

static void append_egg(data_t *data, const unsigned int team_id,
    const int pos_x, const int pos_y)
{
    int nb_eggs = 0;

    nb_eggs = get_nb_eggs(data, data->teams[team_id]->name);
    data->teams[team_id]->eggs = realloc(data->teams[team_id]->eggs,
        sizeof(egg_t *) * (nb_eggs + 2));
    data->teams[team_id]->eggs[nb_eggs] = init_egg(data, pos_x, pos_y);
    data->teams[team_id]->eggs[nb_eggs + 1] = NULL;
    send_enw_to_all_gui(data, data->teams[team_id]->eggs[nb_eggs]);
}

static int fork_cmd(data_t *data, __attribute__((unused)) char **args)
{
    pos_t *player_pos = data->clients[data->curr_cli_index]->player->pos;
    char *team_name = data->clients[data->curr_cli_index]->player->team_name;

    for (int i = 0; data->teams[i]; i++) {
        if (!strcmp(team_name, data->teams[i]->name)) {
            do_pfk(data, data->clients[data->curr_cli_index]->player->id);
            append_egg(data, i, player_pos->x, player_pos->y);
            send_to_client(data->clients, data->curr_cli_index, "ok\n");
            return SUCCESS_STATUS;
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "ko\n");
    return ERROR_STATUS;
}

int schedule_fork(data_t *data, char **args)
{
    if (args != NULL) {
        return ERROR_STATUS;
    }
    append_scheduler_to_queue(data, &fork_cmd, args, FORK_DELAY);
    return SUCCESS_STATUS;
}
