/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_SERVER_IMPLEMENTATION_H
    #define ZAPPY_SERVER_IMPLEMENTATION_H
    #define _GNU_SOURCE

    #include "server_core.h"

    typedef struct cmd_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } cmd_t;

    /**
    * @brief Parse the input from the client
    * @param data * The current server data, clients and current client index
    * @return Status of the parsing / command
    */
    int parse_input(data_t *data);

    /**
    * @brief Get remaining opened slots in a team
    * @param data The current server data, clients and current client index
    * @param team_name The team name to check
    * @return Number of remaining slots
    */
    int get_remaining_slots(data_t *data, char *team_name);

    /**
    * @brief Check if the team name provided by the client is valid and if
    * there is still slots available. If so, the client is added to the team.
    * @param data The current server data, clients and current client index
    * @return Status of the parsing / command
    */
    int parse_team_name(data_t *data);

    /**
    * @brief Sends a response to the msz command sent by the client
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int do_msz(data_t *data, char **args);

    /**
    * @brief Get a string containing the world dimensions of the server
    * @param data The current server data, clients and current client index
    * @return String containing the world dimensions
    */
    char *get_world_dimensions(data_t *data);

    /**
    * @brief Sends a response to the bct command sent by the client
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int do_bct(data_t *data, char **args);

    /**
    * @brief Sends a response to the tna command sent by the client
    * @param data The current server data, clients and current client index
    * @return Status of the parsing / command
    */
    int tna(data_t *data, char **args);
    /**
    * @brief Get frequency
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Frequency
    */
    int do_sgt(data_t *data, char **args);

    /**
    * @brief Sends a response to the forward command sent by the client
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int move_forward(data_t *data, char **args);

    /**
     * @brief Sends a response to the right command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int move_right(data_t *data, char **args);

    /**
     * @brief Sends a response to the left command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int move_left(data_t *data, char **args);

    /**
     * @brief Sends a response to the take command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int take(data_t *data, char **args);

    /**
     * @brief Sends a response to the set command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int set(data_t *data, char **args);
    /**
     * @brief Sends a response to the inventory command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int inventory(data_t *data, char **args);

#endif /* ZAPPY_SERVER_IMPLEMENTATION_H */
