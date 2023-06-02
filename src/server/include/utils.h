/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for utils
*/

#ifndef ZAPPY_UTILS_H
    #define ZAPPY_UTILS_H

    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>

    /**
    * @brief Concatenate two strings
    * @param str1 The first string
    * @param str2 The second string
    * @return char * Concatenated string
    */
    char *concat_str(char *str1, const char *str2);
    /**
    * @brief Generate a sockaddr_in struct
    * @param address The address to bind
    * @param port The port to bind
    * @return The generated struct
    */
    struct sockaddr_in get_sockaddr(in_addr_t address, unsigned int port);
    /**
    * @brief Split a string by a delimiter
    * @param str The string to split
    * @param delim The delimiter
    * @return Array of strings splitted by the delimiter
    */
    char **str_to_word_array(char *str, char *delim);
    /**
    * @brief Free a word array
    * @param words The word array to free
    */
    void free_word_array(char **words);
    /**
    * @brief Get the length of a word array
    * @param words The word array
    * @return The length of the word array
    */
    int word_array_len(char **words);
    /**
    * @brief Convert an int to string
    * @param nbr The int to convert
    * @return The converted string
    */
    char *int_to_s(int nbr);

    /**
    * @brief Reverse a string
    * @param str The string to reverse
    * @return The reversed string
    */
    char *revstr(char *str);

    /**
    * @brief Check if a string can be converted to an int
    * @param p The string to check
    * @return 1 if the string can be converted to an int, 0 otherwise
    */
    int is_int(char const *p);

    /**
    * @brief Get the current time in milliseconds since the Epoch.
    * Epoch corresponds to 00:00:00 UTC, January 1, 1970.
    * @return The current time in milliseconds since epoch
    */
    unsigned long long get_ms_since_epoch(void);

    /**
     * @brief Calculate the coordinates of a player after a forward command
     * @param value The current coordinate (x or y)
     * @param max The maximum value of the coordinate (width or height)
     * @return The new coordinate
     */
    int calc_outbound(int value, int max);

#endif /* ZAPPY_UTILS_H */
