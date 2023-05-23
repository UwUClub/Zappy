/*
** EPITECH PROJECT, 2023
** B-NWP-400-TLS-4-1-zappy-valentin.gegoux
** File description:
** get_file_length
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* @brief return the nbr of lines in a file
** @param filepath
** @return nbr of lines, -1 if error
*/
int get_file_length(char const *filepath)
{
    FILE *fd = fopen(filepath, "r");
    char *buffer = NULL;
    size_t size = 0;
    int lines = 0;

    if (fd == NULL)
        return -1;
    while (getline(&buffer, &size, fd) != -1)
        lines++;
    fclose(fd);
    return lines;
}
