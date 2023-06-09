/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Button
*/

#include "Button.hpp"
#include <OGRE/Overlay/OgreFont.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <iostream>
#include <utility>
#include "Constexpr.hpp"

namespace Zappy::GUI {
    Button::Button(const std::string &aButtonText, const std::pair<int, int> &aPosition,
                   std::function<void()> aCallback)
        : _buttonText(aButtonText),
          _position(aPosition),
          _dimensions(0, 0),
          _callback(std::move(aCallback))
    {
        try {
            Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();
            Ogre::Overlay *myOverlay = overlayManager.getByName(BUTTON_OVERLAY);

            auto *myPanel = overlayManager.createOverlayElement("Panel", aButtonText + "_Panel");
            auto *myContainer = static_cast<Ogre::OverlayContainer *>(myPanel);
            auto *myText = overlayManager.createOverlayElement("TextArea", aButtonText + "_Text");
            auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(myText);
            _dimensions = calculateDimensions();

            myContainer->setMetricsMode(Ogre::GMM_PIXELS);
            myContainer->setPosition(static_cast<Ogre::Real>(_position.first),
                                     static_cast<Ogre::Real>(_position.second));
            myContainer->setDimensions(static_cast<Ogre::Real>(_dimensions.first),
                                       static_cast<Ogre::Real>(_dimensions.second));
            myContainer->setMaterialName("BaseWhite");

            myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
            myTextArea->setPosition(0, 0);
            myTextArea->setCaption(_buttonText);
            myTextArea->setCharHeight(CHAR_HEIGHT);
            myTextArea->setFontName(FONT_NAME, "Zappy");
            myTextArea->setColourTop(Ogre::ColourValue(1, 0, 1));
            myTextArea->setColourBottom(Ogre::ColourValue(0, 0, 0));

            myContainer->addChild(myTextArea);

            myOverlay->add2D(myContainer);
            myPanel->show();
            myContainer->show();
            myText->show();
            myTextArea->show();
            myOverlay->show();
        } catch (const std::exception &e) {
            std::cerr << "Button error : " << e.what() << std::endl;
        }
    }

    Button::~Button() = default;

    std::pair<int, int> Button::calculateDimensions()
    {
        Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().getByName(FONT_NAME, "Zappy");
        const float myCharHeight = myFont->getGlyphAspectRatio('A') * 17;
        float myTextWidth = 0;
        const constexpr float myPaddingX = 1.05F;
        const constexpr float myPaddingY = 1.5F;

        myTextWidth = myCharHeight * static_cast<float>(_buttonText.size()) * myPaddingX;
        return {myTextWidth, static_cast<int>(myCharHeight * myPaddingY)};
    }

    const std::pair<int, int> &Button::getPosition() const
    {
        return _position;
    }

    const std::pair<int, int> &Button::getDimensions() const
    {
        return _dimensions;
    }

    const std::string &Button::getButtonText() const
    {
        return _buttonText;
    }

    bool Button::isOnButton(const Ogre::Vector2 &mousePos) const
    {
        return mousePos.x >= static_cast<Ogre::Real>(_position.first)
               && mousePos.x <= static_cast<Ogre::Real>(_position.first) + static_cast<Ogre::Real>(_dimensions.first)
               && mousePos.y >= static_cast<Ogre::Real>(_position.second)
               && mousePos.y <= static_cast<Ogre::Real>(_position.second) + static_cast<Ogre::Real>(_dimensions.second);
    }

    void Button::onClick()
    {
        _callback();
    }
} // namespace Zappy::GUI