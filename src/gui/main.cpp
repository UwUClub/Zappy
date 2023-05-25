//
// Created by beafowl on 22/05/23.
//

#include <iostream>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::ClientApi clientApi(parserData.getAddress(), parserData.getPort(), "team_name");
        clientApi.joinGame();
        clientApi.sendCommand("Forward");
        while (true) {
            if (clientApi.update() >= 1) {
                break;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
