#include <iostream>
// #include <catch2/catch.hpp>
#include "../src/gui/cli/ClientApi.hpp"
#include "../src/gui/cli/ParserData.hpp"
#include "../src/gui/cli/ServerData.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingBct", "[testingBct]")
{
    char *argv[] = {"./zappy_gui", "-p", "4242"};
    int argc = 3;
    Zappy::GUI::Tile tile;
    Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
    parserData.parseData(argc, argv);
    Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (!myClientApi.getServerData()._mapTiles.empty()) {
            break;
        }
    }
    tile = myClientApi.getServerData()._mapTiles.at(0);
    myClientApi.disconnect();
    REQUIRE(tile._x == 0);
    REQUIRE(tile._y == 0);
    REQUIRE(tile._food == 0);
    REQUIRE(tile._linemate == 0);
    REQUIRE(tile._deraumere == 0);
    REQUIRE(tile._sibur == 0);
    REQUIRE(tile._mendiane == 0);
    REQUIRE(tile._phiras == 0);
    REQUIRE(tile._thystame == 0);
}