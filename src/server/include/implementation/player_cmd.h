/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_PLAYER_CMD_H
    #define ZAPPY_PLAYER_CMD_H

    #define FORWARD_DELAY 7
    #define RIGHT_DELAY 7
    #define LEFT_DELAY 7
    #define LOOK_DELAY 7
    #define INVENTORY_DELAY 1
    #define BROADCAST_DELAY 7
    #define CONNECT_NBR_DELAY 0
    #define FORK_DELAY 42
    #define EJECT_DELAY 7
    #define TAKE_DELAY 7
    #define SET_DELAY 7
    #define INCANTATION_DELAY 300

    #include "implementation.h"

    static const int elevation_secret[7][8] = {
        {2, 1, 1, 0, 0, 0, 0, 0},
        {3, 2, 1, 1, 1, 0, 0, 0},
        {4, 2, 2, 0, 1, 0, 2, 0},
        {5, 4, 1, 1, 2, 0, 1, 0},
        {6, 4, 1, 2, 1, 3, 0, 0},
        {7, 6, 1, 2, 3, 0, 1, 0},
        {8, 6, 2, 2, 2, 2, 2, 1}
    };

    /**
    * @brief Schedule a player command to be executed after a delay
    * @param data The current server data, clients and current client index
    * @param name The name of the command
    * @param args The arguments of the command (NULL if none)
    * @return Status of the parsing / command
    */
    int schedule_player_cmd(data_t *data, char *name, char **args);

    /**
    * @brief Append the scheduler to the player's pending command queue
    * @param data The current server data, clients and current client index
    * @param func The function to execute
    * @param args The arguments of the command (NULL if none)
    * @param delay The delay before executing the command
    */
    void append_scheduler_to_queue(data_t *data, int (*func)(data_t *data,
    char **args), char **args, time_t delay);

    /**
    * @brief Eliminate the top command in the queue and shift the next commands
    * @param data The current server data, clients and current client index
    * @param player_index The index of the player
    */
    void shift_pending_cmd(data_t *data, const int player_index);

    /**
    * @brief Schedule forward command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int schedule_forward(data_t *data, char **args);

    /**
    * @brief Schedule right command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_right(data_t *data, char **args);

    /**
    * @brief Schedule left command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_left(data_t *data, char **args);

    /**
    * @brief Schedule take command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_take(data_t *data, char **args);

    /**
    * @brief Schedule set command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_set(data_t *data, char **args);

    /**
    * @brief Schedule inventory command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_inventory(data_t *data, char **args);

    /**
     * @brief Schedule look command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_look(data_t *data, char **args);

    /**
     * @brief Schedule connect_nbr command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_connect_nbr(data_t *data, char **args);

    /**
     * @brief Schedule fork command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_fork(data_t *data, char **args);

    /**
     * @brief Schedule broadcast command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_broadcast(data_t *data, char **args);

    /**
     * @brief Schedule incantation command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_incantation(data_t *data, char **args);

    /**
     * @brief Check if the incantation is possible (resources and players)
     * @param data The current server data, clients and current client index
     * @param pos The position of the player
     * @param target_lvl The target level
     * @param check_ongoing_cmd Check if players are running a cmd or not
     * @return 1 if the incantation is possible, 0 otherwise
     */
    int check_tile_for_incantation(data_t *data, pos_t *pos,
        const int target_lvl, const int check_ongoing_cmd);

    /**
     * @brief Check if a player is valid for incantation
     * @param clients Client list of the server
     * @param index The index of the player
     * @param pos The position of the incantation
     * @return 1 if the player is valid, 0 otherwise
     */
    int is_player_valid_for_incantation(client_t **clients, const int index,
        pos_t *pos, const int target_lvl);

    /**
     * @brief Schedule eject command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_eject(data_t *data, char **args);

    /**
    * @brief Get tile number from source direction (used for broadcast)
    * @param data The current server data, clients and current client index
    * @param player_id The id of the player
    * @param source_x The x position of the source
    * @param source_y The y position of the source
    * @return Id of the tile
    */
    int get_tile_from_source(data_t *data, const unsigned int player_id,
        const unsigned int source_x, const unsigned int source_y);

    static const cmd_t player_schedulers[] = {
        {"Forward", &schedule_forward, FORWARD_DELAY},
        {"Right", &schedule_right, RIGHT_DELAY},
        {"Left", &schedule_left, LEFT_DELAY},
        {"Take", &schedule_take, TAKE_DELAY},
        {"Set", &schedule_set, SET_DELAY},
        {"Inventory", &schedule_inventory, INVENTORY_DELAY},
        {"Connect_nbr", &schedule_connect_nbr, CONNECT_NBR_DELAY},
        {"Look", &schedule_look, LOOK_DELAY},
        {"Fork", &schedule_fork, FORK_DELAY},
        {"Broadcast", &schedule_broadcast, BROADCAST_DELAY},
        {"Eject", &schedule_eject, EJECT_DELAY},
        {"Incantation", &schedule_incantation, INCANTATION_DELAY},
        {NULL, NULL}
    };

#endif /* ZAPPY_PLAYER_CMD_H */
