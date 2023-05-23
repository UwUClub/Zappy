/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** generate_uuid
*/

#include <uuid/uuid.h>
#include <stdlib.h>
#include "utils.h"

char *generate_uuid(void)
{
    uuid_t uuid;
    char *uuid_str = NULL;

    uuid_str = malloc(sizeof(char) * UUID_LENGTH);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}
