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
    #define NB_LEVELS 8

    #include "core.h"

    static const int level_incantation[7][8] = {{1, 1, 1, 0, 0, 0, 0, 0},
                                            {2, 2, 1, 1, 1, 0, 0, 0},
                                            {3, 2, 2, 0, 1, 0, 2, 0},
                                            {4, 4, 1, 1, 2, 0, 1, 0},
                                            {5, 4, 1, 2, 1, 3, 0, 0},
                                            {6, 6, 1, 2, 3, 0, 1, 0},
                                            {7, 6, 2, 2, 2, 2, 2, 1},
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
    * @brief Get tile number from source direction (used for broadcast)
    * @param data The current server data, clients and current client index
    * @param player_id The id of the player
    * @param source_x The x position of the source
    * @param source_y The y position of the source
    * @return Id of the tile
    */
    int get_tile_from_source(data_t *data, const unsigned int player_id,
        const unsigned int source_x, const unsigned int source_y);

    /**
     * @brief Schedule eject command
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the schedule
     */
    int schedule_eject(data_t *data, char **args);

    /**
     * @brief Check the ressource asked of a tile
     * @param data The current server data, clients and current client index
     * @param ressource The ressource to check
     * @return return the quantity of the ressource in the tile of the player
     */
    int check_tile(data_t *data, int ressource);

    /**
     * @brief Remove all the ressource consummed from a tile
     * @param data The current server data, clients and current client index
     * @return return 0 if success, 1 if error
     */
    int remove_all_ressources_from_tile(data_t *data);

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
        {"Incantation", &schedule_incantation, INCANTATION_DELAY},
        {NULL, NULL}
    };

#endif /* ZAPPY_PLAYER_CMD_H */
