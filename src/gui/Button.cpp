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
    Button::Button(const std::string &aButtonText, const std::pair<int, int> &aPosition)
        : _buttonText(aButtonText),
          _position(aPosition),
          _dimensions(0, 0)
    {
        try {
            Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();
            Ogre::Overlay *myOverlay = overlayManager.getByName(BUTTON_OVERLAY);

            auto *myPanel = overlayManager.createOverlayElement("Panel", "ButtonPanel");
            auto *myContainer = static_cast<Ogre::OverlayContainer *>(myPanel);
            auto *myText = overlayManager.createOverlayElement("TextArea", "ButtonText");
            auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(myText);
            _dimensions = calculateDimensions();

            myContainer->setMetricsMode(Ogre::GMM_PIXELS);
            myContainer->setPosition(_position.first, _position.second);
            myContainer->setDimensions(_dimensions.first, _dimensions.second);
            myContainer->setColour(Ogre::ColourValue(255, 255, 255));
            myContainer->setMaterialName("BaseWhite");

            myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
            myTextArea->setPosition(0, 0);
            myTextArea->setDimensions(100, 100);
            myTextArea->setCaption(_buttonText);
            myTextArea->setCharHeight(16);
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
        const float myCharHeight = myFont->getTrueTypeSize();
        float myTextWidth = 0;

        for (const auto &myChar : _buttonText) {
            const auto myCharWidth = myFont->getGlyphAspectRatio(myChar) * myCharHeight;
            myTextWidth += myCharWidth;
        }
        return {myTextWidth, static_cast<int>(myCharHeight)};
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
} // namespace Zappy::GUI