/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** KeyHandler
*/

#include "EventHandler.hpp"
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreTimer.h>
#include <iostream>

namespace Zappy::GUI {
    EventHandler::EventHandler() = default;

    EventHandler::~EventHandler() = default;

    bool EventHandler::keyPressed(const OgreBites::KeyboardEvent &aEvt)
    {
        if (aEvt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true;
    }

    bool EventHandler::buttonPressed(const OgreBites::ButtonEvent &aEvt)
    {
        std::cout << "Button pressed " << aEvt.button << std::endl;
        return true;
    }

} // namespace Zappy::GUI
