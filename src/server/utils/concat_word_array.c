/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** concat_word_array
*/

#include <string.h>
#include "utils.h"

char *concat_word_array(char **args)
{
    char *msg = NULL;

    msg = strdup("");
    for (int i = 0; args[i]; i++) {
        if (i > 0)
            msg = concat_str(msg, " ");
        msg = concat_str(msg, args[i]);
    }
    return msg;
}
