#include <iostream>
#include "../../src/server/implementation/player/get_player_by_id.c"
#include <catch2/catch_test_macros.hpp>

player_t *init_player(const int id, const char *team_name, orientation_t orientation)
{
    player_t *player = (player_t *) malloc(sizeof(player_t));

    player->id = id;
    player->pos = NULL;
    player->orientation = orientation;
    player->level = 1;
    player->inventory[0] = 0;
    player->team_name = strdup(team_name);
    player->pending_cmd_queue[0] = NULL;
    player->remaining_digestion_ms = 0;
    player->is_freezed = false;
    return player;
}

client_t *init_player_client(const int id, const char *team_name, orientation_t orientation)
{
    client_t *client = (client_t *) malloc(sizeof(client_t));

    client->fd = 0;
    client->is_registered = true;
    client->player = init_player(id, team_name, orientation);
    client->input = NULL;
    client->output = NULL;
    return client;
}

void free_client(client_t *client)
{
    if (client->player != NULL) {
        free(client->player->team_name);
        free(client->player);
    }
    free(client);
}

void free_clients(client_t **clients)
{
    for (int i = 0; clients[i] != NULL; i++) {
        free_client(clients[i]);
    }
    free(clients);
}

TEST_CASE("testingGetPlayerById1", "[testingGetPlayerById1]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 4);
    player_t *player = NULL;

    clients[0] = init_player_client(15, "Team1", NORTH);
    clients[1] = init_player_client(42, "Team2", EAST);
    clients[2] = init_player_client(86, "Team3", SOUTH);
    clients[3] = NULL;
    player = get_player_by_id(clients, 42);
    REQUIRE(player != NULL);
    REQUIRE(player != NULL);
    REQUIRE(player->id == 42);
    REQUIRE(!strcmp(player->team_name, "Team2"));
    REQUIRE(player->orientation == EAST);
    free_clients(clients);
}

TEST_CASE("testingGetPlayerById2", "[testingGetPlayerById2]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 4);
    player_t *player = NULL;

    clients[0] = init_player_client(15, "Team1", NORTH);
    clients[1] = init_player_client(42, "Team2", EAST);
    clients[2] = init_player_client(86, "Team3", SOUTH);
    clients[3] = NULL;
    player = get_player_by_id(clients, 15);
    REQUIRE(player != NULL);
    REQUIRE(player->id == 15);
    REQUIRE(!strcmp(player->team_name, "Team1"));
    REQUIRE(player->orientation == NORTH);
    free_clients(clients);
}

TEST_CASE("testingGetPlayerById3", "[testingGetPlayerById3]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 4);
    player_t *player = NULL;

    clients[0] = init_player_client(15, "Team1", NORTH);
    clients[1] = init_player_client(42, "Team2", EAST);
    clients[2] = init_player_client(86, "Team3", SOUTH);
    clients[3] = NULL;
    player = get_player_by_id(clients, 86);
    REQUIRE(player != NULL);
    REQUIRE(player->id == 86);
    REQUIRE(!strcmp(player->team_name, "Team3"));
    REQUIRE(player->orientation == SOUTH);
    free_clients(clients);
}

TEST_CASE("testingGetPlayerById4", "[testingGetPlayerById4]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 4);
    player_t *player = NULL;

    clients[0] = init_player_client(15, "Team1", NORTH);
    clients[1] = init_player_client(42, "Team2", EAST);
    clients[2] = init_player_client(86, "Team3", SOUTH);
    clients[3] = NULL;
    player = get_player_by_id(clients, 0);
    REQUIRE(player == NULL);
    free_clients(clients);
}
