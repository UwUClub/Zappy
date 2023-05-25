//
// Created by beafowl on 22/05/23.
//

#include "ClientApi.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Hello, world!" << std::endl;
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::ClientApi clientApi(parserData.getAddress(), parserData.getPort(), parserData.getTeamName());
        clientApi.joinGame();
        while (true) {
            if (clientApi.update() >= 1) { break; }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    // std::cout << "connectStatus: " << clientApi.getConnectStatus() << std::endl;
    // std::cout << "sock fd: " << clientApi.getServerFd() << std::endl;
    return 0;
}
