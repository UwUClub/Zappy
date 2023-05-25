//
// Created by beafowl on 22/05/23.
//

#include <iostream>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    try {
        Zappy::GUI::ParserData myParserData("127.0.0.1", 0, "");
        myParserData.parseData(argc, argv);
        Zappy::GUI::ClientApi myClientApi(myParserData.getAddress(), myParserData.getPort(), "");
        myClientApi.joinGame();
        while (true) {
            if (myClientApi.update() >= 1) {
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
