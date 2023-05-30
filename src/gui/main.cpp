//
// Created by beafowl on 22/05/23.
//

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main()
{
    // try {
    //     Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
    //     parserData.parseData(argc, argv);
    //     Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "team_name");
    //     myClientApi.joinGame();
    //     while (true) {
    //         if (myClientApi.update() >= 1) {
    //             break;
    //         }
    //     }
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // }
    // return 0;
    OgreBites::ApplicationContext ctx("Zappy");
    ctx.initApp();
}
