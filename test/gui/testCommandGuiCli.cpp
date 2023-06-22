#include "ClientApi.hpp"
#include "ParserData.hpp"
#include "App.hpp"
#include "Mediator.hpp"
#include "ServerData.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto SERVER_PORT = 4242;

TEST_CASE("testingBct", "[testingBct]")
{
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

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
    REQUIRE(myClientApi.getServerData()._mapTiles.empty() == false);
}

TEST_CASE("testingMsz", "[testingMsz]")
{
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

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
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

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
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (myClientApi.getServerData()._players.empty()) {
            break;
        }
        if (myClientApi.getServerData()._players.at(0).getPosition().first != 0) {
            break;
        }
    }
    if (myClientApi.getServerData()._players.empty()) {
        std::cout << "no player found" << std::endl;
        return;
    }
    myClientApi.disconnect();
    REQUIRE(myClientApi.getServerData()._players.at(0).getPosition().first);
    REQUIRE(myClientApi.getServerData()._players.at(0).getPosition().second);
}

TEST_CASE("testingPlv", "[testingPlv]")
{
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (myClientApi.getServerData()._players.empty()) {
            break;
        }
        if (myClientApi.getServerData()._players.at(0).getLevel() != 0) {
            break;
        }
    }
    if (myClientApi.getServerData()._players.empty()) {
        std::cout << "no player found" << std::endl;
        return;
    }
    myClientApi.disconnect();
    REQUIRE(myClientApi.getServerData()._players.at(0).getLevel() != 0);
}

TEST_CASE("testingEnw", "[testingEnw]")
{
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (!myClientApi.getServerData()._eggs.empty()) {
            break;
        }
    }
    myClientApi.disconnect();
    REQUIRE(!myClientApi.getServerData()._eggs.empty());
}

TEST_CASE("testingSgt", "[testingSgt]")
{
    Zappy::GUI::ParserData parserData(SERVER_IP, SERVER_PORT, "");
    Zappy::GUI::ServerData myServerData;
    Zappy::GUI::Mediator myMediator(parserData);
    Zappy::GUI::ClientApi myClientApi("127.0.0.1", 4242, "GRAPHIC", myMediator, myServerData);

    myClientApi.joinGame();
    while (true) {
        if (myClientApi.update() >= 1) {
            break;
        }
        if (myClientApi.getServerData()._freq != 0) {
            break;
        }
    }
    myClientApi.disconnect();
    REQUIRE(myClientApi.getServerData()._freq != 0);
}
