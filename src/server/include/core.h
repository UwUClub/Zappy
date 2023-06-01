/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server network
*/

#ifndef ZAPPY_SERVER_CORE_H
    #define ZAPPY_SERVER_CORE_H

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

    typedef struct pending_cmd_s {
        int (*func)(data_t *data, char **args);
        char **args;
        time_t remaining;
    } pending_cmd_t;

    typedef struct player_s {
        int pos_x;
        int pos_y;
        orientation_t orientation;
        int level;
        int inventory[TILE_SIZE];
        char *team_name;
        pending_cmd_t *pending_cmd_queue[MAX_PENDING_CMD];
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

    typedef struct data_s {
        int curr_cli_index;
        client_t **clients;
        map_t *map;
        char **team_names;
        int cli_per_team;
        int freq;
        int port;
        time_t last_select;
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
    * @brief Init the data structure that includes all the data needed for
    * the server
    * @return The data structure
    */
    data_t *init_server_data(int ac, char **av);

    /**
    * @brief Free the data structure once the server is closed
    * @param data The data structure to free
    */
    void free_server_data(data_t *data);

    /**
    * @brief Parse the arguments passed to the server
    * @param data The data structure to set
    * @param ac The number of arguments
    * @param av The arguments
    * @return Status of the parsing
    */
    int parse_data_options(data_t *data, int ac, char **av);

    /**
    * @brief Print the help message
    * @param data To follow the option pattern
    * @param value To follow the option pattern
    * @return Status of the printing
    */
    int print_help(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_port(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_map_width(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_map_height(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_team_names(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_cli_per_team(data_t *data, char *value);

    /**
    * @brief Set the data structure with the arguments passed to the server
    * @param data The data structure to set
    * @param value The value to set
    * @return Status of the parsing
    */
    int set_freq(data_t *data, char *value);

    /**
    * @brief Free the data structure once the server is closed
    * @param data The data structure to free
    */
    void free_data(data_t *data);

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
    int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data);

    /**
    * @brief Calculate remaning time or execute pending commands
    * @param data The server data
    */
    void handle_pending_cmd(data_t *data);

    /**
    * @brief Append a message to the client write buffer
    * @param clients Client list of the server
    * @param id Recipient id
    * @param msg Message to append
    */
    void send_to_client(client_t **clients, const int id, const char *msg);

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
    * @param clients Client list of the server
    */
    void welcome_selected_client(struct sockaddr *addr, int server_fd,
    client_t ***clients);

    /**
    * @brief Read the client input and append it to his read buffer
    * @param clients Client list of the server
    */
    void read_selected_client(data_t *data);

    /**
    * @brief Write the client output and append it to his write buffer
    * @param clients Client to write to
    */
    void write_to_selected_client(client_t **client);

    /**
    * @brief Spawn resources on the map
    * @param data The server data
    */
    void spawn_resources(data_t *data);

    /**
    * @brief Handle SIGINT signal by stopping the server
    * @param dummy To follow the signal pattern
    */
    void detect_ctrl_c(int dummy);

#endif /* ZAPPY_SERVER_CORE_H */
