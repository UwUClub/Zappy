/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pic
*/

#include "player_cmd.h"
#include "utils.h"

void do_pic(data_t *data, player_t *author)
{
    char *msg = NULL;
    char *str_id = NULL;

    asprintf(&msg, "pic %d %d %d %d ", author->pos->x, author->pos->y,
        author->level, author->id);
    for (int i = 0; data->clients[i]; i++) {
        if (is_player_valid_for_incantation(data->clients, i, author->pos,
        author->level + 1) && data->clients[i]->player->id != author->id){
            str_id = int_to_s(data->clients[i]->player->id);
            msg = concat_str(msg, str_id);
            msg = concat_str(msg, " ");
            free(str_id);
        }
    }
    msg = concat_str(msg, "\n");
    send_to_all_gui(data->clients, msg);
    free(msg);
}
