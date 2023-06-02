#include <OGRE/OgreSceneManager.h>
#include <iostream>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main(int argc, char **argv)
{
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
        myClientApi.joinGame();
        while (true) {
            if (myClientApi.update() >= 1) {
                break;
            }
            myClientApi.update();
            myClientApi.sendCommand("pin 4");
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
