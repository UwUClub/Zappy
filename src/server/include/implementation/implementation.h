/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_IMPLEMENTATION_H
    #define ZAPPY_IMPLEMENTATION_H

    #include "core.h"

    typedef struct cmd_s {
        char *name;
        int (*func)(data_t *data, char **args);
        time_t delay;
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
    * @brief Register client as gui
    * @param data The current server data, clients and current client index
    * @return Status of the registration
    */
    int append_gui_client(data_t *data);

    /**
    * @brief Register client as player
    * @param data The current server data, clients and current client index
    * @param team_name The team name to check
    * @return Status of the registration
    */
    int append_player_client(data_t *data, char *team_name);

    /**
    * @brief Get a string containing the world dimensions of the server
    * @param data The current server data, clients and current client index
    * @return String containing the world dimensions
    */
    char *get_world_dimensions(data_t *data);

    /**
    * @brief Calculate remaning time or execute pending commands
    * @param data The server data
    * @param elapsed_time_ms The elapsed time since the last call
    */
    void handle_pending_cmd(data_t *data,
        unsigned long long elapsed_time_ms);

    /**
    * @brief Make player consume food and kill him if he has no food anymore
    * @param data The current server data, clients and current client index
    * @param elapsed_time_ms The elapsed time since the last call
    */
    void handle_player_digestion(data_t *data,
        unsigned long long elapsed_time_ms);

#endif /* ZAPPY_IMPLEMENTATION_H */
