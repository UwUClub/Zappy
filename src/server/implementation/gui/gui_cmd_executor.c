/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** gui_cmd_executor
*/

#include "implementation.h"
#include "gui_cmd.h"
#include "utils.h"

static int check_cmd_status(data_t *data, int (*func)(data_t *data,
    char **args), char **args)
{
    int status = 0;

    status = func(data, args);
    if (status == ERROR_STATUS) {
        send_to_client(data->clients, data->curr_cli_index, "sbp\n");
    }
    free_word_array(args);
    return status;
}

int execute_gui_cmd(data_t *data, char *cmd_name, char **args)
{
    for (int i = 0; gui_commands[i].name != NULL; i++) {
        if (!strcmp(cmd_name, gui_commands[i].name)) {
            return check_cmd_status(data, gui_commands[i].func, args);
        }
    }
    send_to_client(data->clients, data->curr_cli_index, "suc\n");
    free_word_array(args);
    return ERROR_STATUS;
}
