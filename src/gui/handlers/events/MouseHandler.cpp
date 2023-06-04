/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MouseHandler
*/

#include "MouseHandler.hpp"

namespace Zappy::GUI {
    MouseHandler::MouseHandler()
        : _isLeftClickPressed(false),
          _isRightClickPressed(false)
    {}

    MouseHandler::~MouseHandler() = default;

    bool MouseHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
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

    bool MouseHandler::mouseReleased(const OgreBites::MouseButtonEvent &aEvt)
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
} // namespace Zappy::GUI