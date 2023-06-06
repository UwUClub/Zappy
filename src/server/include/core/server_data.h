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
    void init_teams(data_t *data);

    /**
     * @brief Free teams
     * @param data The structure that includes server data,
     */
    void free_teams(data_t *data);

#endif /* ZAPPY_SERVER_DATA_H */
