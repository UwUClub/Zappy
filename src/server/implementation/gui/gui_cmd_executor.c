/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** gui_cmd_executor
*/

#include "implementation.h"
#include "gui_cmd.h"
#include "utils.h"

static const cmd_t commands[] = {
    {"msz", &do_msz, 0},
    {"bct", &do_bct, 0},
    {"tna", &do_tna, 0},
    {"sgt", &do_sgt, 0},
    {"pin", &do_pin, 0},
    {"ppo", &do_ppo, 0},
    {NULL, NULL}
};

static int check_cmd_status(data_t *data, int (*func)(data_t *data,
    char **args), char **args)
{
    int status = 0;

    status = func(data, args);
    if (status == 1) {
        send_to_client(data->clients, data->curr_cli_index, "sbp\n");
    }
    free_word_array(args);
    return status;
}

int execute_gui_cmd(data_t *data, char *cmd_name, char **args)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (!strcmp(cmd_name, commands[i].name)) {
            return check_cmd_status(data, commands[i].func, args);
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "suc\n");
    return 84;
}
