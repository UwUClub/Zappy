/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** FrameHandler
*/

#include "FrameHandler.hpp"
#include <iostream>

namespace Zappy::GUI {
    FrameHandler::FrameHandler(Ogre::SceneManager *aSceneManager, Zappy::GUI::ClientApi &client)
        : _sceneManager(aSceneManager),
          _client(client)
    {}

    FrameHandler::~FrameHandler() = default;

    bool FrameHandler::frameRenderingQueued(const Ogre::FrameEvent &evt)
    {
        // std::cout << "FrameHandler::frameRenderingQueued" << std::endl;
        return true;
    }

    bool FrameHandler::frameStarted(const Ogre::FrameEvent &aEvt)
    {
        return true;
    }

    bool FrameHandler::frameEnded(const Ogre::FrameEvent &evt)
    {
        // std::cout << "FrameHandler::frameEnded" << std::endl;
        return true;
    }
} // namespace Zappy::GUI