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
        if (is_player(data, i) && i != data->curr_cli_index) {
            origin_tile = get_tile_from_source(data, i, sender->pos_x,
                sender->pos_y);
            asprintf(&msg, "message %d, %s\n", origin_tile, content);
            send_to_client(data->clients, i, msg);
            free(msg);
            msg = NULL;
        }
    }
}

static void send_broadcast_to_gui(data_t *data, const char *content)
{
    char *msg = NULL;

    asprintf(&msg, "pbc %d %s\n", data->curr_cli_index, content);
    send_to_all_gui(data->clients, msg);
    free(msg);
}

static int broadcast(data_t *data, char **args)
{
    char *content = NULL;

    content = concat_word_array(args);
    send_broadcast_to_gui(data, content);
    send_broadcast_to_players(data, content);
    free(content);
    return 0;
}

int schedule_broadcast(data_t *data, char **args)
{
    if (!args) {
        return 1;
    }
    append_scheduler_to_queue(data, &broadcast, args, BROADCAST_DELAY);
    return 0;
}
