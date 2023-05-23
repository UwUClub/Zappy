/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** get_client
*/

#include "server_core.h"

client_t **get_clients_by_uuid(client_t **clients, char *uuid)
{
    client_t **result = NULL;
    int j = 0;

    result = malloc(sizeof(client_t *) * (MAX_CONNECTIONS + 1));
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->uuid && !strcmp(clients[i]->uuid, uuid)) {
            result[j] = clients[i];
            j++;
        }
    }
    result[j] = NULL;
    return result;
}
