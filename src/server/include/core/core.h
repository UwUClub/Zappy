/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server network
*/

#ifndef ZAPPY_SERVER_CORE_H
    #define ZAPPY_SERVER_CORE_H

    #define _GNU_SOURCE

    #define SUCCESS_STATUS 0
    #define ERROR_STATUS 84

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "ranges.h"

    typedef struct data_s data_t;

    typedef enum orientation_e {
        UNKNOWN = 0,
        NORTH,
        EAST,
        SOUTH,
        WEST,
        END
    } orientation_t;

    typedef struct pos_s {
        int x;
        int y;
    } pos_t;

    typedef struct pending_cmd_s {
        int (*func)(data_t *data, char **args);
        char **args;
        unsigned long long remaining_ms;
    } pending_cmd_t;

    typedef struct player_s {
        int id;
        pos_t *pos;
        orientation_t orientation;
        int level;
        int inventory[TILE_SIZE];
        char *team_name;
        pending_cmd_t *pending_cmd_queue[MAX_PENDING_CMD];
        unsigned long long remaining_digestion_ms;
        int is_freezed;
    } player_t;

    typedef struct client_s {
        int fd;
        int is_registered;
        player_t *player;
        char *input;
        char *output;
    } client_t;

    typedef struct map_s {
        int width;
        int height;
        int (**tiles)[TILE_SIZE];
    } map_t;

    typedef struct egg_s {
        int id;
        int progenitor_id;
        pos_t *pos;
        unsigned long long remaining_digestion_ms;
        int food;
    } egg_t;

    typedef struct team_s {
        char *name;
        egg_t **eggs;
    } team_t;

    typedef struct saved_opt_s {
        char **team_names;
        int nb_cli_per_team;
    } saved_opt_t;

    typedef struct data_s {
        int curr_cli_index;
        client_t **clients;
        map_t *map;
        team_t **teams;
        int freq;
        int port;
        unsigned long long last_select_ms;
        char *ip;
        unsigned long long remaining_rsrc_spawn_ms;
        int nb_clients;
        int nb_slots;
    } data_t;

    typedef struct option_s {
        char flag;
        int (*func)(data_t *data, char *value);
    } option_t;

    typedef struct instruction_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } instruction_t;

    /**
    * @brief Launch the server
    * @param data_t *data
    * @return Status of the server
    */
    int launch_server(data_t *data);

    /**
    * @brief Initialize a client
    * @param client The client to initialize
    */
    void init_single_client(client_t **client);

    /**
    * @brief Initialize a player in a client
    * @param client The client to initialize
    * @param team_name The team name of the player
    * @param map_width The width of the map
    * @param map_height The height of the map
    */
    void init_player(client_t **client, const char *team_name, map_t *map);
    /**
    * @brief Close a client
    * @param client The client to close
    */
    void close_single_client(client_t *client);

    /**
    * @brief Close all the clients
    * @param clients Client list of the server
    */
    void close_clients(client_t **clients);

    /**
    * @brief Get the next select() timeout
    * @param data The server data
    * @return The next select() timeout
    */
    struct timeval *get_next_timeout(data_t *data);

    /**
    * @brief Handle read / write flow a client
    * @param addr The server address
    * @param server_fd The server file descriptor
    * @param data The structure that includes server data,
    * clients and current client index
    * @return 1 if the server is closing, 0 otherwise
    */
    int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data,
        struct timeval *timeout);

    /**
    * @brief Append a message to the client write buffer
    * @param clients Client list of the server
    * @param id Recipient id
    * @param msg Message to append
    */
    void send_to_client(client_t **clients, const int id, const char *msg);

    /**
     * @brief Append a message to all GUI clients in the server
     * @param clients Client list of the server
     * @param msg Message to append
    */
    void send_to_all_gui(client_t **clients, const char *msg);

    /**
    * @brief Append a message to all clients in the server
    * @param clients Client list of the server
    * @param msg Message to append
    */
    void send_to_everyone(client_t **clients, const char *msg);

    /**
    * @brief Welcome a client who joined the server by sending him a
    * WELCOME message and initializing his data
    * @param addr the client address
    * @param server_fd the server file descriptor
    * @param data The server data
    */
    void welcome_selected_client(struct sockaddr *addr, int server_fd,
    data_t *data);

    /**
    * @brief Read the client input and append it to his read buffer
    * @param clients Client list of the server
    */
    void read_selected_client(data_t *data);

    /**
    * @brief Write the client output and append it to his write buffer
    * @param data The structure that includes server data,
    * clients and current client index
    * @param clients Client to write to
    * @return 1 if the client quits, 0 otherwise
    */
    int write_to_selected_client(data_t *data, client_t **client);

    /**
    * @brief Update remaining time before next resurce spawn. If remaining time
    * is 0, spawn resources on the map
    * @param data The server data
    * @param elapsed_time_ms The elapsed time since the last call
    */
    void handle_resource_spawn(data_t *data,
        unsigned long long elapsed_time_ms);

    /**
    * @brief Handle SIGINT signal by stopping the server
    * @param dummy To follow the signal pattern
    */
    void detect_ctrl_c(int dummy);

    /**
     * @brief Send to gui the end of game if there is a winner
     * @param data The current server data, clients and current client index
     * @return Status of the parsing / command
     */
    int detect_win(data_t *data);

    /**
     * @brief Return all the player on a tile
     * @param data The server data
     * @param x The x position of the tile
     * @param y The y position of the tile
     * @return The list of player on the tile
     */
    client_t **check_player_on_tile(data_t *data, const int x, const int y);

    /**
     * @brief Handle quit by closing client and sending pdi to gui
     * @param data The structure that includes server data,
     * clients and current client index
     * @return The list of player on the tile
     */
    void handle_client_quit(data_t *data);

#endif /* ZAPPY_SERVER_CORE_H */
