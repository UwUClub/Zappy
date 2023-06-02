/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** get_ms_since_epoch
*/

#include <sys/time.h>
#include <stddef.h>
#include "ranges.h"

unsigned long long get_ms_since_epoch(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    unsigned long long ms_since_epoch =
        (unsigned long long)(tv.tv_sec) * MS_FACTOR +
        (unsigned long long)(tv.tv_usec) / MS_FACTOR;
    return ms_since_epoch;
}
