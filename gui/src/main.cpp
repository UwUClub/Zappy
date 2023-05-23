//
// Created by beafowl on 22/05/23.
//

#include "ClientApi.hpp"
#include <iostream>

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    std::cout << "Hello, world!" << std::endl;
    Zappy::GUI::ClientApi clientApi("127.0.0.1", 4242, "a");
    clientApi.joinGame();
    while (true) {
        if (clientApi.update() >= 1) { break; }
    }
    // std::cout << "connectStatus: " << clientApi.getConnectStatus() << std::endl;
    // std::cout << "sock fd: " << clientApi.getServerFd() << std::endl;
    return 0;
}
