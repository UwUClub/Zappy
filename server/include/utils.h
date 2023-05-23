/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** Header for utils
*/

#ifndef MYTEAMS_UTILS_H
    #define MYTEAMS_UTILS_H

    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>

    #define UUID_LENGTH 37
    #define __USE_XOPEN
    #define _GNU_SOURCE

    char *concat_str(char *str1, const char *str2);
    struct sockaddr_in get_sockaddr(in_addr_t address, unsigned int port);
    char **str_to_word_array(char *str, char *delim);
    void free_word_array(char **words);
    int word_array_len(char **words);
    char **parse_quotes(const char *str);
    char *generate_uuid(void);
    int get_file_length(char const *filepath);
    char *inttos(int nbr);
    char *revstr(char *str);
    time_t str_to_time(char *str);
    void rm_line_from_file(const char *filename, int line_to_delete);
    int is_int(char const *p);

#endif /* MYTEAMS_UTILS_H */
