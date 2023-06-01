//
// Created by beafowl on 22/05/23.
//

#include "App.hpp"
#include "ParserData.hpp"

int main(int argc, const char **argv)
{
    // try {
    // Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
    //     parserData.parseData(argc, argv);
    // Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "team_name");
    //     myClientApi.joinGame();
    //     while (true) {
    //         if (myClientApi.update() >= 1) {
    //             break;
    //         }
    //     }
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // }
    Zappy::GUI::App ctx("Zappy");
    std::cout << "Hello, World!" << std::endl;
    // camNode->lookAt(node->_getDerivedPosition(), Ogre::Node::TS_WORLD);
    ctx.getRoot()->startRendering();
    std::cout << "Hello, World 2!" << std::endl;
    return 0;
}
