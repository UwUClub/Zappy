/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** print_help
*/

#include "core.h"

int print_help(__attribute__((unused)) data_t *data,
    __attribute__((unused)) char *value)
{
    int status = 0;

    status = dprintf(2, "\nUSAGE: ./zappy_server -p port -x width -y height ");
    dprintf(2, "-n name1 name2 ... -c clientsNb -f freq\n\n");
    dprintf(2, "\tport\t\tis the port number\n");
    dprintf(2, "\twidth\t\tis the width of the world\n");
    dprintf(2, "\theight\t\tis the height of the world\n");
    dprintf(2, "\tnameX\t\tis the name of the team X\n");
    dprintf(2, "\tclientsNb\tis the number of authorized clients per team\n");
    dprintf(2, "\tfreq\t\tis the reciprocal of time unit for execution ");
    dprintf(2, "of actions\n\n");
    return status;
}
