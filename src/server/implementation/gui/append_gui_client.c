/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** append_gui_client
*/

#include "implementation.h"
#include "utils.h"
#include "gui_cmd.h"
#include "player_cmd.h"

int append_gui_client(data_t *data)
{
    char *x_str = NULL;
    char *y_str = NULL;

    do_msz(data, NULL);
    do_sgt(data, NULL);
    for (int x = 0; x < data->map->width; x++) {
        for (int y = 0; y < data->map->height; y++) {
            x_str = int_to_s(x);
            y_str = int_to_s(y);
            do_bct(data, (char *[]){x_str, y_str, NULL});
            free(x_str);
            free(y_str);
        }
    }
    do_tna(data, NULL);
    return 0;
}
