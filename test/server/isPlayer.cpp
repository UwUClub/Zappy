#include <iostream>
#include "../../src/server/implementation/player/is_player.c"
#include "/usr/src/project/vcpkg/installed/x64-linux/include/catch.hpp"

TEST_CASE("testingIsPlayer1", "[testingIsPlayer2]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 2);

    clients[0] = (client_t *) malloc(sizeof(client_t));
    clients[0]->fd = 0;
    clients[0]->is_registered = true;
    clients[0]->player = NULL;
    clients[0]->input = NULL;
    clients[0]->output = NULL;
    clients[1] = NULL;
    REQUIRE(is_player(clients, 0) == false);
    free(clients[0]);
    free(clients);
}

TEST_CASE("testIsPlayer2", "[testIsPlayer2]")
{
    client_t **clients = (client_t **) malloc(sizeof(client_t *) * 2);

    clients[0] = (client_t *) malloc(sizeof(client_t));
    clients[0]->fd = 0;
    clients[0]->is_registered = true;
    clients[0]->player = (player_t *) malloc(sizeof(player_t));
    clients[0]->player->id = 0;
    clients[0]->player->pos = NULL;
    clients[0]->player->orientation = NORTH;
    clients[0]->player->level = 1;
    clients[0]->player->inventory[0] = 0;
    clients[0]->player->team_name = strdup("Team1");
    clients[0]->player->pending_cmd_queue[0] = NULL;
    clients[0]->player->remaining_digestion_ms = 0;
    clients[0]->player->is_freezed = false;
    clients[0]->input = NULL;
    clients[0]->output = NULL;
    clients[1] = NULL;
    REQUIRE(is_player(clients, 0) == true);
    free(clients[0]->player->team_name);
    free(clients[0]->player);
    free(clients[0]);
    free(clients);
}
