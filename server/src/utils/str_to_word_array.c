/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <string.h>

char **str_to_word_array(char *str, char *delim)
{
    char **result = NULL;
    char *token = NULL;
    int i = 0;

    result = malloc(sizeof(char *) * (strlen(str) + 1));
    token = strtok(str, delim);
    while (token != NULL) {
        result[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(result[i], token);
        token = strtok(NULL, delim);
        i++;
    }
    result[i] = NULL;
    return result;
}
