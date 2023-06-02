/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_PLAYER_CMD_H
    #define ZAPPY_PLAYER_CMD_H

    #define _GNU_SOURCE

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

    #include "core.h"

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
    * @brief Sends a response to the forward command sent by the client
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int move_forward(data_t *data, char **args);

    /**
    * @brief Schedule right command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_right(data_t *data, char **args);

    /**
     * @brief Sends a response to the right command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int move_right(data_t *data, char **args);

    /**
    * @brief Schedule left command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_left(data_t *data, char **args);

    /**
     * @brief Sends a response to the left command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int move_left(data_t *data, char **args);

    /**
    * @brief Schedule take command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_take(data_t *data, char **args);

    /**
     * @brief Sends a response to the take command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int take(data_t *data, char **args);

    /**
    * @brief Schedule set command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_set(data_t *data, char **args);

    /**
     * @brief Sends a response to the set command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int set(data_t *data, char **args);

    /**
    * @brief Schedule inventory command
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the schedule
    */
    int schedule_inventory(data_t *data, char **args);

    /**
     * @brief Sends a response to the inventory command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int get_inventory(data_t *data, char **args);

    /**
     * @brief Sends a response to the look command sent by the client
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
     */
    int look(data_t *data, char **args);

#endif /* ZAPPY_PLAYER_CMD_H */
