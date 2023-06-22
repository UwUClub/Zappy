/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sst
*/

#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"

int do_sst(data_t *data, char **args)
{
    int freq = 0;

    if (!args || word_array_len(args) != 1) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return ERROR_STATUS;
    }
    freq = atoi(args[0]);
    if (freq <= 0) {
        send_to_client(data->clients, data->curr_cli_index, "ko\n");
        return ERROR_STATUS;
    }
    data->freq = freq;
    send_to_client(data->clients, data->curr_cli_index, "ok\n");
    do_sgt_to_all_gui(data);
    return SUCCESS_STATUS;
}
