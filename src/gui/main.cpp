//
// Created by beafowl on 22/05/23.
//

#include <iostream>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main(int argc, char **argv)
{
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::ClientApi clientApi(parserData.getAddress(), parserData.getPort(), "");
        clientApi.joinGame();
        while (true) {
            if (clientApi.update() >= 1) {
                break;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    // std::cout << "connectStatus: " << clientApi.getConnectStatus() << std::endl;
    // std::cout << "sock fd: " << clientApi.getServerFd() << std::endl;
    return 0;
}
