/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** normalize_pos
*/

#include "core.h"
#include "utils.h"

void normalize_pos(pos_t *pos, const int width, const int height)
{
    pos->x = calc_outbound(pos->x, width);
    pos->y = calc_outbound(pos->y, height);
}
