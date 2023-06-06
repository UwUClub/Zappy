/*
** EPITECH PROJECT, 2023
** testing_cmake
** File description:
** is_ip.c
*/

static int check_char(char elem, int *dots, int *digits)
{
    if (elem == '.') {
        (*dots)++;
        (*digits) = 0;
        return 1;
    } else if (elem >= '0' && elem <= '9') {
        (*digits)++;
        return 1;
    } else {
        return 0;
    }
}

int is_ip(char const *str)
{
    int i = 0;
    int dots = 0;
    int digits = 0;

    while (str[i] != '\0') {
        if (check_char(str[i], &dots, &digits) == 0)
            return 0;
        i++;
    }
    if (dots != 3)
        return 0;
    return 1;
}
