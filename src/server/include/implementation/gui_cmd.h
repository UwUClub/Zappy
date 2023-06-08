/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_GUI_CMD_H
    #define ZAPPY_GUI_CMD_H

    #include "implementation.h"

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
     * @brief Sends a response to the bct command sent by the client to all gui
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_bct_to_all_gui(data_t *data, char **args);

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
     * @brief Set the new frequency given
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_sst(data_t *data, char **args);

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
     * @brief Sends player id and level to gui
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_plv(data_t *data, char **args);

    /**
     * @brief Sends player id and level to all gui
     * @param data The current server data, clients and current client index
     * @param player The player to show
    */
    void send_plv_to_all_gui(data_t *data, player_t *player);

    /**
     * @brief Sends player id, position and orientation to gui
     * @param data The current server data, clients and current client index
     * @param args The arguments of the command
     * @return Status of the parsing / command
    */
    int do_ppo(data_t *data, char **args);

    /**
     * @brief Sends player id, position and orientation to all gui
     * @param data The current server data, clients and current client index
     * @param player The player to show
    */
    void send_ppo_to_all_gui(data_t *data, player_t *player);

    /**
     * @brief Sends egg progenitor to gui
     * @param data The current server data, clients and current client index
     * @param player_id The id of the player
    */
    void do_pfk(data_t *data, const unsigned int player_id);

    /**
     * @brief Sends egg progenitor, id and position to gui
     * @param data The current server data, clients and current client index
     * @param egg The egg to show
    */
    void do_enw(data_t *data, egg_t *egg);

    /**
     * @brief Notify player connection to gui
     * @param data The current server data, clients and current client index
    */
    void do_pnw(data_t *data);

    /**
     * @brief Notify to gui that a player was born and replaced an egg
     * @param data The current server data, clients and current client index
    */
    void do_ebo(data_t *data);

    /**
     * @brief Notify to gui that an egg hatched
     * @param data The current server data, clients and current client index
    */
    void do_edi(data_t *data, const int egg_index);

    /**
     * @brief Notify to gui that a player took an object
     * @param data The current server data, clients and current client index
     * @param resource The id of the resource taken
    */
    int do_pgt(data_t *data, int resource);

    /**
     * @brief Notify to gui that a player dropped an object
     * @param data The current server data, clients and current client index
     * @param resource The id of the resource dropped
    */
    int do_pdr(data_t *data, int resource);

    static const cmd_t gui_commands[] = {
        {"msz", &do_msz, 0},
        {"bct", &do_bct, 0},
        {"tna", &do_tna, 0},
        {"sgt", &do_sgt, 0},
        {"sst", &do_sst, 0},
        {"pin", &do_pin, 0},
        {"plv", &do_plv, 0},
        {"ppo", &do_ppo, 0},
        {NULL, NULL}
    };

#endif /* ZAPPY_GUI_CMD_H */
