/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for ranges
*/

#ifndef ZAPPY_RANGES_H
    #define ZAPPY_RANGES_H

    #define MAX_TEAMS 4
    #define MAX_CLI_PER_TEAM 10

    #define MAX_CLIENTS (MAX_TEAMS * MAX_CLI_PER_TEAM + MAX_TEAMS)

    #define READ_BUFFER_SIZE 1024

    #define MIN_MAP_SIZE 10
    #define MAX_MAP_SIZE 30
    #define TILE_SIZE 7

    #define MIN_FREQ 2
    #define MAX_FREQ 1000

    #define MAX_PENDING_CMD 11

    #define MS_FACTOR 1000

#endif /* ZAPPY_RANGES_H */
