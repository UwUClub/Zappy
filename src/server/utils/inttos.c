/*
** EPITECH PROJECT, 2021
** my_inttos
** File description:
** integer to string
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

static int my_intlen(int nbr)
{
    if (nbr == 0)
        return nbr;
    return (my_intlen(nbr / 10) + 1);
}

static char *rec_inttos(int nbr, int index, char *str)
{
    if (nbr == 0) {
        return "0";
    }
    rec_inttos(nbr / 10, index + 1, str);
    str[index] = ((char) nbr) % 10 + '0';
    return str;
}

/* @brief Converts an integer to a string.
 * @param nbr The integer to convert.
 * @return An allocated string representation of the integer nbr.
 */
char *inttos(int nbr)
{
    char *str = NULL;
    int length = 0;

    length = my_intlen(nbr);
    if (nbr == 0) {
        return "0";
    }
    if (nbr < 0)
        length++;
    str = malloc(sizeof(char) * ((unsigned int) (length + 1)));
    memset(str, '0', (size_t) length);
    if (nbr < 0) {
        str[length - 1] = '-';
        nbr *= -1;
    }
    str[length] = '\0';
    str = rec_inttos(nbr, 0, str);
    str = revstr(str);
    return str;
}
