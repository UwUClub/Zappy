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
            myContainer->setPosition(300, 300);
            myContainer->setDimensions(500, 500);
            myContainer->setColour(Ogre::ColourValue(255, 255, 255));

            myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
            myTextArea->setPosition(0, 0);
            myTextArea->setDimensions(100, 100);
            myTextArea->setCaption(aButtonText);
            myTextArea->setCharHeight(16);
            myTextArea->setFontName(FONT_NAME, "Zappy");
            myTextArea->setColourBottom(Ogre::ColourValue(1, 1, 1));
            myTextArea->setColourTop(Ogre::ColourValue(1, 1, 1));

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

    Button::~Button()
    {}
} // namespace Zappy::GUI