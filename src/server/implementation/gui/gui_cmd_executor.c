/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** gui_cmd_executor
*/

#include "implementation.h"
#include "gui_cmd.h"

static const cmd_t commands[] = {
    {"msz", &do_msz},
    {"bct", &do_bct},
    {"tna", &do_tna},
    {"sgt", &do_sgt},
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
