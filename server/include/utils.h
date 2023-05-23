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

    char *concat_str(char *str1, const char *str2);
    struct sockaddr_in get_sockaddr(in_addr_t address, unsigned int port);
    char **str_to_word_array(char *str, char *delim);
    void free_word_array(char **words);
    int word_array_len(char **words);
    char **parse_quotes(const char *str);
    int get_file_length(char const *filepath);
    char *inttos(int nbr);
    char *revstr(char *str);
    void rm_line_from_file(const char *filename, int line_to_delete);
    int is_int(char const *p);

#endif /* ZAPPY_UTILS_H */
