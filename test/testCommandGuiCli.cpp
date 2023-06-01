#include <iostream>
#include "../src/gui/cli/ClientApi.hpp"
#include "../src/gui/cli/ParserData.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto SERVER_PORT = 4242;

TEST_CASE("testingBct", "[testingBct]")
{
    Zappy::GUI::Tile const tile = {};
    Zappy::GUI::ParserData const parserData(SERVER_IP, SERVER_PORT, "");
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
    Zappy::GUI::ParserData const parserData(SERVER_IP, SERVER_PORT, "");
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

TEST_CASE("testingTna", "[testingTna]")
{
    Zappy::GUI::ParserData const parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (!myClientApi.getServerData()._teamNames.empty()) {
            break;
        }
    }
    myClientApi.disconnect();
    REQUIRE(!myClientApi.getServerData()._teamNames.empty());
}

TEST_CASE("testingPpo", "[testingPpo]")
{
    Zappy::GUI::ParserData const parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (!myClientApi.getServerData()._teamNames.empty()) {
            break;
        }
    }
    myClientApi.disconnect();
    REQUIRE(!myClientApi.getServerData()._teamNames.empty());
}