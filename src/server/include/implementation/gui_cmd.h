/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_GUI_CMD_H
    #define ZAPPY_GUI_CMD_H

    #include "core.h"

    /**
    * @brief Executes the command sent by the client
    * @param data The current server data, clients and current client index
    * @param cmd The command sent by the client
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int execute_gui_cmd(data_t *data, char *cmd, char **args);

    /**
    * @brief Sends a response to the msz command sent by the client
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Status of the parsing / command
    */
    int do_msz(data_t *data, char **args);

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
    int do_tna(data_t *data, char **args);

    /**
    * @brief Get frequency
    * @param data The current server data, clients and current client index
    * @param args The arguments of the command
    * @return Frequency
    */
    int do_sgt(data_t *data, char **args);

    /**
     * @brief Sends to the gui the end of the game
     * @param data The current server data, clients and current client index
     * @param team_name The name of the team that won
     * @return Status of the parsing / command
    */
    int do_seg(data_t *data, const char *team_name);

    /**
     * @brief Sends player id, position and inventory to gui
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_pin(data_t *data, char **args);

    /**
     * @brief Sends player id, position and orientation to gui
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_ppo(data_t *data, char **args);

#endif /* ZAPPY_GUI_CMD_H */
