/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** do_mct
*/

#include "core.h"
#include "gui_cmd.h"

int do_mct(data_t *data, __attribute__((unused)) char **args)
{
    char *x_str = NULL;
    char *y_str = NULL;

    if (args && args[0]) {
        return ERROR_STATUS;
    }
    for (int y = 0; y < data->map->height; y++) {
        for (int x = 0; x < data->map->width; x++) {
            asprintf(&x_str, "%d", x);
            asprintf(&y_str, "%d", y);
            send_bct_to_current_cli(data, (char *[]){x_str, y_str, NULL});
            free(x_str);
            free(y_str);
        }
    }
    return SUCCESS_STATUS;
}
