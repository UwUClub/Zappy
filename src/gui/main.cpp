//
// Created by beafowl on 22/05/23.
//

#include <OGRE/OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <iostream>
#include <thread>
#include "App.hpp"
#include "ClientApi.hpp"
#include "Mediator.hpp"
#include "ParserData.hpp"

int main(int argc, char **argv)
{
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::Mediator mediator(parserData);

        mediator.start();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
