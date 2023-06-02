/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** calc_outbound
*/

int calc_outbound(int value, int max)
{
    if (value < 0)
        return max + value;
    if (value >= max)
        return value - max;
    return value;
}
