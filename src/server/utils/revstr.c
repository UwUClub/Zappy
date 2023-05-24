/*
** EPITECH PROJECT, 2021
** my_revstr
** File description:
** reverses a string.
*/

#include <stddef.h>
#include <string.h>

/* @brief Reverses a string.
 * @param str The string to reverse.
 * @return The reversed string.
 */
char *revstr(char *str)
{
    char temp;
    int cmpt = 0;
    int rev_cmpt;
    int len;

    len = strlen(str);
    rev_cmpt = len - 1;
    while (rev_cmpt - cmpt > 0) {
        temp = str[cmpt];
        str[cmpt] = str[rev_cmpt];
        str[rev_cmpt] = temp;
        cmpt++;
        rev_cmpt--;
    }
    return str;
}
