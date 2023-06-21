/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** seg
*/

#include "implementation.h"
#include "utils.h"

int do_seg(data_t *data, const char *team_name)
{
    char *msg = NULL;

    if (team_name == NULL)
        return SUCCESS_STATUS;
    msg = strdup("seg ");
    msg = concat_str(msg, team_name);
    msg = concat_str(msg, "\n");
    send_to_all_gui(data->clients, msg);
    free(msg);
    return ERROR_STATUS;
}
