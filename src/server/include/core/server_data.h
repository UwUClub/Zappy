/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server data
*/

#ifndef ZAPPY_SERVER_DATA_H
    #define ZAPPY_SERVER_DATA_H

    #include "core.h"

    /**
    * @brief Init the data structure that includes all the data needed for
    * the server
    * @return The data structure
    */
    data_t *init_server_data(int ac, char **av);

    /**
    * @brief Free the data structure once the server is closed
    * @param data The data structure to free
    */
    void free_server_data(data_t *data);

    /**
     * @brief Init map tiles with no resources
     * @param data The structure that includes server data,
     * clients and current client index
     */
    void init_map_tiles(data_t *data);

    /**
     * @brief Init teams
     * @param data The structure that includes server data,
     * clients and current client index
     */
    void init_teams(data_t *data, char **team_names,
        const unsigned int nb_egg_per_team);

    /**
     * @brief Free teams
     * @param data The structure that includes server data,
     * clients and current client index
     */
    void free_teams(data_t *data);

    /**
     * @brief Init an egg
     * @param data The structure that includes server data,
     * clients and current client index
     * @param pos_x The x position of the egg
     * @param pos_y The y position of the egg
     * @return The egg
     */
    egg_t *init_egg(data_t *data, const unsigned int pos_x,
        const unsigned int pos_y);

    /**
     * @brief Free an egg
     * @param egg The egg to free
     */
    void free_egg(egg_t *egg);

#endif /* ZAPPY_SERVER_DATA_H */
