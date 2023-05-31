#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "../src/gui/cli/ClientApi.hpp"
#include "../src/gui/cli/ParserData.hpp"
#include "../src/gui/cli/ServerData.hpp"

TEST_CASE("testingBct", "[testingBct]")
{
    Zappy::GUI::Tile const tile = {};
    Zappy::GUI::ParserData const parserData("127.0.0.1", 4242, "");
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
    myClientApi.disconnect();
    REQUIRE(myClientApi.getServerData()._mapTiles.empty() == false);
}

TEST_CASE("testingMsz", "[testingMsz]")
{
    Zappy::GUI::ParserData const parserData("127.0.0.1", 4242, "");
    Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (myClientApi.getServerData()._mapSize.first) {
            break;
        }
    }
    myClientApi.disconnect();
    REQUIRE(myClientApi.getServerData()._mapSize.first == 10);
    REQUIRE(myClientApi.getServerData()._mapSize.second == 10);
}
