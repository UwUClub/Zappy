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
     * @brief Send to gui the end of game
     * @param data The current server data, clients and current client index
     * @param is_ctrl_c If the end of game is due to a ctrl c
     * @return Status of the parsing / command
     */
    int detect_win(data_t *data, int is_ctrl_c);

#endif /* ZAPPY_GUI_CMD_H */
