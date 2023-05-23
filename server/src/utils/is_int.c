/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** is_int
*/

int is_int(char const *str)
{
    while (*str != '\0') {
        if (*str < 48 || *str > 57)
            return 0;
        str++;
    }
    return 1;
}
