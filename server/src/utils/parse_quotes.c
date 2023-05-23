/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** parse_quotes
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void add_word(char **result, const char *str, int *i, int n)
{
    int j = *i + 1;

    for (; str[j] != '\"'; j++);
    result[n] = strndup(str + *i + 1, j - *i - 1);
    *i = j;
}

int even_quotes(const char *str)
{
    int n = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            n++;
    }
    return n % 2 == 0;
}

char **parse_quotes(const char *str)
{
    char **result = NULL;
    int n = 0;

    if (!even_quotes(str))
        return NULL;
    result = malloc(sizeof(char *) * (strlen(str) + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"') {
            add_word(result, str, &i, n);
            n++;
        }
    }
    result[n] = NULL;
    return result;
}
