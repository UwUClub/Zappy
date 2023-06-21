/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Button
*/

#include "Button.hpp"
#include <OGRE/Overlay/OgreFont.h>
#include <OGRE/Overlay/OgreOverlay.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <iostream>
#include <utility>
#include "Constexpr.hpp"
#include "SceneBuilder.hpp"

namespace Zappy::GUI {
    Button::Button(const std::string &aButtonText, const std::pair<float, float> &aPosition,
                   const std::pair<float, float> &aDimension, std::function<void()> aCallback)
        : _buttonText(aButtonText),
          _position(aPosition),
          _dimensions(aDimension),
          _isDisplayed(true),
          _callback(std::move(aCallback))
    {
        try {
            SceneBuilder::createText(
                BUTTON_OVERLAY, _buttonText, _buttonText, Ogre::Vector2(_position.first, _position.second),
                Ogre::Vector2(_dimensions.first, _dimensions.second), "Textbox", RESSOURCE_GROUP_NAME,
                Ogre::Vector2(_dimensions.first - 325, OFFSET_OVERLAY_BUTTON_TIME_Y));
        } catch (const std::exception &e) {
            std::cerr << "Button error : " << e.what() << std::endl;
        }
    }

    Button::~Button() = default;

    bool Button::isOnButton(const Ogre::Vector2 &mousePos) const
    {
        if (!_isDisplayed)
            return false;
        return mousePos.x >= static_cast<Ogre::Real>(_position.first)
               && mousePos.x <= static_cast<Ogre::Real>(_position.first) + static_cast<Ogre::Real>(_dimensions.first)
               && mousePos.y >= static_cast<Ogre::Real>(_position.second)
               && mousePos.y <= static_cast<Ogre::Real>(_position.second) + static_cast<Ogre::Real>(_dimensions.second);
    }

    void Button::onClick()
    {
        _callback();
    }

    void Button::setDisplayed(bool displayed)
    {
        Ogre::OverlayManager &myOverlayManager = Ogre::OverlayManager::getSingleton();

        _isDisplayed = displayed;
        if (displayed) {
            myOverlayManager.getOverlayElement(_buttonText + "_Panel")->show();
            myOverlayManager.getOverlayElement(_buttonText + "_Text")->show();
            return;
        }
        myOverlayManager.getOverlayElement(_buttonText + "_Panel")->hide();
        myOverlayManager.getOverlayElement(_buttonText + "_Text")->hide();
    }
} // namespace Zappy::GUI