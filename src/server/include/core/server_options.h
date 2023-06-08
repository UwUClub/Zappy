/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for options
*/

#ifndef ZAPPY_SERVER_OPTIONS_H
    #define ZAPPY_SERVER_OPTIONS_H

    #include "core.h"

    /**
    * @brief Parse the arguments passed to the server
    * @param data The data structure to set
    * @param ac The number of arguments
    * @param av The arguments
    * @return Status of the parsing
    */
    int parse_data_options(data_t *data, saved_opt_t *saved, int ac, char **av);

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
    int set_freq(data_t *data, char *value);

    /**
     * @brief Set the ip of the server
     * @param data The data structure to set
     * @param value The value to set
     * @return Status of the parsing
     */
    int set_ip(data_t *data, char *value);

    static const option_t options[] = {
        { 'h', &print_help },
        { 'p', &set_port },
        { 'x', &set_map_width },
        { 'y', &set_map_height },
        { 'f', &set_freq },
        { 'v', &set_ip },
        { -1, NULL }
    };

#endif //ZAPPY_SERVER_OPTIONS_H
