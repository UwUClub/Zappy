/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** FrameHandler
*/

#include "FrameHandler.hpp"
#include <iostream>

namespace Zappy::GUI {
    FrameHandler::FrameHandler(Ogre::SceneManager *aSceneManager)
        : _sceneManager(aSceneManager)
    {}

    FrameHandler::~FrameHandler() = default;

    bool FrameHandler::frameRenderingQueued(const Ogre::FrameEvent &evt)
    {
        // std::cout << "FrameHandler::frameRenderingQueued" << std::endl;
        return true;
    }

    bool FrameHandler::frameStarted(const Ogre::FrameEvent &evt)
    {
        // std::cout << "FrameHandler::frameStarted" << std::endl;
        try {
            // get node called 0 0 from scene manager, it's a node added to the root node
            // Ogre::SceneNode *myNode = _sceneManager.getSceneNode("0 0");
            // myNode->translate(0, 0.1, 0);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        return true;
    }

    bool FrameHandler::frameEnded(const Ogre::FrameEvent &evt)
    {
        // std::cout << "FrameHandler::frameEnded" << std::endl;
        return true;
    }
} // namespace Zappy::GUI