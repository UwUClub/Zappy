/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MouseHandler
*/

#include "InputHandler.hpp"
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreRoot.h>

namespace Zappy::GUI {
    InputHandler::InputHandler(ClientApi &client)
        : _isLeftClickPressed(false),
          _isRightClickPressed(false),
          _isShiftPressed(false),
          _client(client)
    {}

    InputHandler::~InputHandler() = default;

    bool InputHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
    {
        if (aEvt.button == OgreBites::BUTTON_RIGHT) {
            _isRightClickPressed = true;
            return true;
        }
        if (aEvt.button == OgreBites::BUTTON_LEFT) {
            _isLeftClickPressed = true;
            return true;
        }
        return true;
    }

    bool InputHandler::mouseReleased(const OgreBites::MouseButtonEvent &aEvt)
    {
        if (aEvt.button == OgreBites::BUTTON_RIGHT) {
            _isRightClickPressed = false;
            return true;
        }
        if (aEvt.button == OgreBites::BUTTON_LEFT) {
            _isLeftClickPressed = false;
            return true;
        }
        return true;
    }

    bool InputHandler::keyPressed(const OgreBites::KeyboardEvent &aEvt)
    {
        if (aEvt.keysym.sym == OgreBites::SDLK_LSHIFT) {
            _isShiftPressed = true;
            return true;
        }
        if (aEvt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
            _client.disconnect();
        }
        return true;
    }

    bool InputHandler::keyReleased(const OgreBites::KeyboardEvent &aEvt)
    {
        if (aEvt.keysym.sym == OgreBites::SDLK_LSHIFT) {
            _isShiftPressed = false;
            return true;
        }
        return true;
    }
} // namespace Zappy::GUI
