/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sst
*/

#include <stdio.h>
#include "implementation.h"
#include "utils.h"

int do_sst(data_t *data, char **args)
{
    int freq = 0;

    if (!args || word_array_len(args) != 1) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 1;
    }
    freq = atoi(args[0]);
    if (freq <= 0) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return 1;
    }
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    data->freq = freq;
    return 0;
}
