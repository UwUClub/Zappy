/*
** EPITECH PROJECT, 2023
** testing_cmake
** File description:
** is_ip.c
*/

int is_ip(char const *str)
{
    int i = 0;
    int dots = 0;
    int digits = 0;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            dots++;
            digits = 0;
        } else if (str[i] >= '0' && str[i] <= '9') {
            digits++;
        } else {
            return 0;
        }
        if (digits > 3 || dots > 3)
            return 0;
        i++;
    }
    if (dots != 3)
        return 0;
    return 1;
}
