/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** clients_lifecycle
*/

#include "core.h"
#include "resources.h"
#include "default_values.h"

void init_single_client(client_t **client)
{
    (*client)->fd = -1;
    (*client)->is_registered = 0;
    (*client)->player = NULL;
    (*client)->input = NULL;
    (*client)->output = strdup("");
}

void init_player(client_t **client, const char *team_name, map_t *map)
{
    (*client)->player = malloc(sizeof(player_t));
    (*client)->player->pos = malloc(sizeof(pos_t));
    (*client)->player->pos->x = rand() % map->width;
    (*client)->player->pos->y = rand() % map->height;
    (*client)->player->orientation = NORTH;
    (*client)->player->level = LEVEL_START;
    (*client)->player->inventory[0] = FOOD_START;
    for (int i = 1; i < TILE_SIZE; i++) {
        (*client)->player->inventory[i] = 0;
    }
    (*client)->player->team_name = strdup(team_name);
    for (int i = 0; i < MAX_PENDING_CMD; i++) {
        (*client)->player->pending_cmd_queue[i] = NULL;
    }
    (*client)->player->remaining_digestion_ms = 0;
}

static void close_single_player(client_t *client)
{
    if (client->player == NULL)
        return;
    if (client->player->team_name != NULL)
        free(client->player->team_name);
    if (client->player->pos != NULL)
        free(client->player->pos);
    for (int i = 0; i < MAX_PENDING_CMD; i++) {
        if (client->player->pending_cmd_queue[i] != NULL) {
            free(client->player->pending_cmd_queue[i]);
        }
    }
    free(client->player);
}

void close_single_client(client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    close_single_player(client);
    if (client->input != NULL)
        free(client->input);
    if (client->output != NULL)
        free(client->output);
}

void close_clients(client_t **clients)
{
    for (int i = 0; clients[i]; i++) {
        close_single_client(clients[i]);
        free(clients[i]);
    }
    free(clients);
}
