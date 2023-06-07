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
     * @brief Check if the client is a player
     * @param data The current server data, clients and current client index
     * @param i The index of the player
     * @return 1 if the player is a player, 0 otherwise
     */
    int is_player(data_t *data, const int i);

    /** @brief Calculate remaning time or execute pending commands
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

    /**
    * @brief Kill current player defined in data by sending him a death message
    * The server closes the client socket once the message is sent
    * @param data The current server data, clients and current client index
    */
    void kill_player(data_t *data);

    /**
    * @brief Get the player by his id
    * @param data The current server data, clients and current client index
    * @param id The id of the player
    * @return The player if found, NULL otherwise
    */
    player_t *get_player_by_id(data_t *data, const unsigned int id);

    /**
    * @brief Get the number of eggs in a team
    * @param data The current server data, clients and current client index
    * @param team_name Name of the team
    * @return The number of eggs in the team
    */
    int get_nb_eggs(data_t *data, const char *team_name);

    /**
    * @brief Get a team by its name
    * @param teams The teams array
    * @param name The name of the team
    * @return The team if found, NULL otherwise
    */
    team_t *get_team_by_name(team_t **teams, const char *name);

#endif /* ZAPPY_IMPLEMENTATION_H */
