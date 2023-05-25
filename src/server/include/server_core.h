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
    #include <sys/select.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #define MAX_TEAMS 4

    typedef enum orientation_e {
        UNKNOWN = 0,
        NORTH,
        EAST,
        SOUTH,
        WEST
    } orientation_t;

    typedef struct client_s {
        int fd;
        int pos_x;
        int pos_y;
        orientation_t orientation;
        int level;
        int inventory[7];
        char *team_name;
        char *input;
        char *output;
    } client_t;

    typedef struct map_s {
        int width;
        int height;
        int **tiles;
    } map_t;

    typedef struct data_s {
        int curr_cli_index;
        client_t **clients;
        map_t *map;
        char **team_names;
        int cli_per_team;
        int freq;
    } data_t;

    typedef struct instruction_s {
        char *name;
        int (*func)(data_t *data, char **args);
    } instruction_t;

    /** 
    * @brief Init the data structure that includes all the data needed for
    * the server
    * @return The data structure
    */
    data_t *init_data();
    /** 
    * @brief Free the data structure once the server is closed
    * @param data The data structure to free
    */
    void free_data(data_t *data);
    /**
    * @brief Launch the server
    * @param unsigned int port
    * @param data_t *data
    * @return Status of the server
    */
    int launch_server(unsigned int port, data_t *data);
    /**
    * @brief Initialize a client
    * @param client The client to initialize
    */
    void init_single_client(client_t **client);
    /**
    * @brief Close a client
    * @param client The client to close
    */
    void close_single_client(client_t *client);
    /**
    * @brief Initialize all the clients
    * @param max_connections The maximum number of connections
    * @return The client list
    */
    client_t **init_clients(const unsigned int max_connections);
    /**
    * @brief Close all the clients
    * @param clients Client list of the server
    */
    void close_clients(client_t **clients);
    /**
    * @brief Handle read / write flow a client
    * @param addr The server address
    * @param server_fd The server file descriptor
    * @param data The structure that includes server data,
    * clients and current client index
    */
    void select_clients(struct sockaddr_in *addr, int server_fd, data_t *data);
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
    client_t **clients);
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

#endif /* ZAPPY_SERVER_CORE_H */
