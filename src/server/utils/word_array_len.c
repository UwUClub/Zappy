/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** word_array_len
*/

#include <stdlib.h>

int word_array_len(char **words)
{
    int i = 0;

    if (words == NULL)
        return 0;
    while (words[i] != NULL) {
        i++;
    }
    return i;
}
