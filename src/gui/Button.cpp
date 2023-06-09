/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Button
*/

#include "Button.hpp"
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <iostream>
#include "Constexpr.hpp"

namespace Zappy::GUI {
    Button::Button(const std::string &aButtonText)
    {
        try {
            Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

            Ogre::Overlay *myOverlay = overlayManager.getByName(BUTTON_OVERLAY);

            auto *myPanel = overlayManager.createOverlayElement("Panel", "ButtonPanel");
            auto *myContainer = static_cast<Ogre::OverlayContainer *>(myPanel);
            auto *myText = overlayManager.createOverlayElement("TextArea", "ButtonText");
            auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(myText);

            myContainer->setMetricsMode(Ogre::GMM_PIXELS);
            myContainer->setPosition(30, 30);
            myContainer->setDimensions(100, 100);
            myContainer->setMaterialName("BaseWhite");

            myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
            myTextArea->setPosition(0, 0);
            myTextArea->setDimensions(100, 100);
            myTextArea->setCaption(aButtonText);
            myTextArea->setCharHeight(16);
            myTextArea->setFontName("BTTF.ttf");
            myTextArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
            myTextArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

            myContainer->addChild(myTextArea);

            myOverlay->add2D(myContainer);
            myOverlay->show();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    Button::~Button()
    {}
} // namespace Zappy::GUI