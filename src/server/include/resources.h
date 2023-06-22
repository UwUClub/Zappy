/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for resources
*/

#ifndef ZAPPY_RESOURCES_H
    #define ZAPPY_RESOURCES_H

    #define NB_RESOURCES 7
    #define SPAWN_INTERVAL 20
    #define FOOD_START 10
    #define DIGESTION_TIME 126

    typedef enum resource_e {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    } resource_t;

    #define FOOD_NAME "food"
    #define LINEMATE_NAME "linemate"
    #define DERAUMERE_NAME "deraumere"
    #define SIBUR_NAME "sibur"
    #define MENDIANE_NAME "mendiane"
    #define PHIRAS_NAME "phiras"
    #define THYSTAME_NAME "thystame"

    #define FOOD_DENSITY      0.5
    #define LINEMATE_DENSITY  0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY     0.1
    #define MENDIANE_DENSITY  0.1
    #define PHIRAS_DENSITY    0.08
    #define THYSTAME_DENSITY  0.05

    static const float resource_densities[NB_RESOURCES] = {
        FOOD_DENSITY, LINEMATE_DENSITY, DERAUMERE_DENSITY, SIBUR_DENSITY,
        MENDIANE_DENSITY, PHIRAS_DENSITY, THYSTAME_DENSITY
    };

    static const char *resource_names[NB_RESOURCES] = {
        FOOD_NAME, LINEMATE_NAME, DERAUMERE_NAME, SIBUR_NAME, MENDIANE_NAME,
        PHIRAS_NAME, THYSTAME_NAME
    };

#endif /* ZAPPY_RESOURCES_H */
