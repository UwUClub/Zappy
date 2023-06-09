/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** free_word_array
*/

#include <stdlib.h>

void free_word_array(char **words)
{
    int i = 0;

    if (!words)
        return;
    while (words[i]) {
        free(words[i]);
        i++;
    }
    free(words);
}
