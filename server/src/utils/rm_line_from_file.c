/*
** EPITECH PROJECT, 2023
** teams
** File description:
** rm_line_from_file
*/

#include <stdio.h>
#include <stdlib.h>

void rm_line_from_file(const char *filename, int line_to_delete)
{
    FILE *input_file = fopen(filename, "r");
    FILE *temp_file = fopen("temp.txt", "w");
    int current_line = 1;
    char buffer[1024];

    if (!input_file || !temp_file)
        return;
    while (fgets(buffer, 1024, input_file)) {
        if (current_line != line_to_delete)
            fputs(buffer, temp_file);
        current_line++;
    }
    fclose(input_file);
    fclose(temp_file);
    remove(filename);
    rename("temp.txt", filename);
}
