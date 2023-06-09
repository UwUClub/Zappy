/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** broadcast
*/

#include "implementation.h"
#include "player_cmd.h"
#include "utils.h"

static void send_broadcast_to_players(data_t *data, const char *content)
{
    player_t *sender = data->clients[data->curr_cli_index]->player;
    char *msg = NULL;
    int origin_tile = 0;

    for (int i = 0; data->clients[i]; i++) {
        if (is_player(data->clients, i) && i != data->curr_cli_index) {
            origin_tile = get_tile_from_source(data, i, sender->pos->x,
                sender->pos->y);
            asprintf(&msg, "message %d, %s\n", origin_tile, content);
            send_to_client(data->clients, i, msg);
            free(msg);
            msg = NULL;
        }
    }
}

static void send_broadcast_to_gui(data_t *data, const char *content)
{
    int curr_cli_id = data->clients[data->curr_cli_index]->player->id;
    char *msg = NULL;

    asprintf(&msg, "pbc %d %s\n", curr_cli_id, content);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

static int broadcast(data_t *data, char **args)
{
    char *content = NULL;

    content = concat_word_array(args);
    send_broadcast_to_gui(data, content);
    send_broadcast_to_players(data, content);
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    free(content);
    return SUCCESS_STATUS;
}

int schedule_broadcast(data_t *data, char **args)
{
    if (!args) {
        return ERROR_STATUS;
    }
    append_scheduler_to_queue(data, &broadcast, args, BROADCAST_DELAY);
    return SUCCESS_STATUS;
}
