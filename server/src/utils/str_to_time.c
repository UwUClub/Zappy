/*
** EPITECH PROJECT, 2021
** my_revstr
** File description:
** str_to_time
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include <time.h>

time_t str_to_time(char *str)
{
    struct tm tm;
    time_t t;

    memset(&tm, 0, sizeof(struct tm));
    strptime(str, "%s", &tm);
    t = mktime(&tm);
    return t;
}
