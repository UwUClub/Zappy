/*
** EPITECH PROJECT, 2023
** zap
** File description:
** EntityFactory
*/

#include "ElementFactory.hpp"
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreEntity.h>
#include <OgreOverlay.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <iostream>
#include "App.hpp"
#include "Constexpr.hpp"
#include "EggData.hpp"
#include "PlayerData.hpp"

namespace Zappy::GUI {
    void ElementFactory::createTile(Ogre::SceneManager *aSceneManager, const Ogre::Vector2 &aPosition,
                                    const std::string &aName)
    {
        static const constexpr Ogre::Real myScale = 0.05F;
        static const constexpr int myTileSize = 1;

        try {
            Ogre::Entity *myEntity = aSceneManager->createEntity(aName, TILE_MODEL_NAME);
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(aName);

            myNode->attachObject(myEntity);
            myNode->setPosition(static_cast<float>(aPosition.x) * (myTileSize * MAP_OFFSET), 0,
                                static_cast<float>(aPosition.y) * (myTileSize * MAP_OFFSET));
            myNode->setScale(myScale, myScale, myScale);
        } catch (Ogre::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void ElementFactory::createPlayer(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayerData)
    {
        static const constexpr Ogre::Real myScale = 0.5F;

        try {
            Ogre::Entity *myEntity = aSceneManager->createEntity(aPlayerData.getId(), PLAYER_MODEL_NAME);
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(aPlayerData.getId());

            myNode->attachObject(myEntity);
            myNode->setScale(myScale, myScale, myScale);

            App::setPlayerPosAndOrientation(aSceneManager, aPlayerData);
        } catch (Ogre::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void ElementFactory::createEgg(Ogre::SceneManager *aSceneManager, const EggData &aEggData)
    {
        static const constexpr Ogre::Real myScale = 0.5F;
        static const constexpr int myAngle = 90;
        const std::string myEggName = "Egg_" + std::to_string(aEggData.getId());

        try {
            Ogre::Entity *myEntity = aSceneManager->createEntity(myEggName, EGG_MODEL_NAME);
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myEggName);

            myNode->attachObject(myEntity);
            myNode->setScale(myScale, myScale, myScale);
            myNode->setOrientation(Ogre::Quaternion(Ogre::Degree(-myAngle), Ogre::Vector3::UNIT_X));
            myNode->setPosition(static_cast<float>(aEggData.getPosition().first * MAP_OFFSET) + EGG_OFFSET_POS,
                                EGG_Y_POS,
                                static_cast<float>(aEggData.getPosition().second * MAP_OFFSET) + EGG_OFFSET_POS);

        } catch (Ogre::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::pair<float, float> ElementFactory::createText(const std::string &aOverlayName, const std::string &aText,
                                                       const std::string &aPrefix, const Ogre::Vector2 &aPosition,
                                                       const std::string &aMaterialName)
    {
        Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();
        Ogre::Overlay *myOverlay = overlayManager.getByName(aOverlayName);

        auto *myContainer =
            static_cast<Ogre::OverlayContainer *>(overlayManager.createOverlayElement("Panel", aPrefix + "_Panel"));
        auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(
            overlayManager.createOverlayElement("TextArea", aPrefix + "_Text"));
        Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().getByName(FONT_NAME, RESSOURCE_GROUP_NAME);
        auto myDimensions = calculateDimensions(aText);

        myContainer->setMetricsMode(Ogre::GMM_PIXELS);
        myContainer->setPosition(aPosition.x, aPosition.y);
        myContainer->setDimensions(myDimensions.first, myDimensions.second);
        myContainer->setMaterialName(aMaterialName);

        myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        myTextArea->setPosition(0, 0);
        myTextArea->setCaption(aText);
        myTextArea->setCharHeight(CHAR_HEIGHT);
        myTextArea->setFontName(FONT_NAME, RESSOURCE_GROUP_NAME);
        myTextArea->setColourTop(Ogre::ColourValue(1, 0, 1));
        myTextArea->setColourBottom(Ogre::ColourValue(0, 0, 0));

        myContainer->addChild(myTextArea);

        myOverlay->add2D(myContainer);
        myOverlay->show();
        return myDimensions;
    }

    std::pair<float, float> ElementFactory::calculateDimensions(const std::string &aButtonText)
    {
        Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().getByName(FONT_NAME, RESSOURCE_GROUP_NAME);
        const float myCharHeight = myFont->getGlyphAspectRatio('A') * 17;
        float myTextWidth = 0;
        const constexpr float myPaddingX = 1.05F;
        const constexpr float myPaddingY = 1.5F;

        myTextWidth = myCharHeight * static_cast<float>(aButtonText.size()) * myPaddingX;
        return {myTextWidth, static_cast<int>(myCharHeight * myPaddingY)};
    }
} // namespace Zappy::GUI