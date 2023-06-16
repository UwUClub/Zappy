/*
** EPITECH PROJECT, 2023
** zap
** File description:
** SceneBuilder
*/

#include "SceneBuilder.hpp"
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreEntity.h>
#include <OgreOverlay.h>
#include <OgrePrerequisites.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <iostream>
#include "App.hpp"
#include "CameraHandler.hpp"
#include "ClickHandler.hpp"
#include "Constexpr.hpp"
#include "OGRE/OgreRenderWindow.h"
#include "PlayerData.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    void SceneBuilder::buildLights(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenter)
    {
        const constexpr int myLightOffsetY = 60;
        const constexpr int myLightOffsetZ = 5;

        Ogre::Light *myLight = aSceneManager->createLight("MainLight");
        myLight->setType(Ogre::Light::LT_DIRECTIONAL);
        myLight->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
        myLight->setSpecularColour(Ogre::ColourValue(1.0, 1.0, 1.0));

        Ogre::SceneNode *myLightNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myLightNode->setDirection(Ogre::Vector3(0, -1, 1));
        myLightNode->setPosition(aCenter + Ogre::Vector3(0, myLightOffsetY, myLightOffsetZ));
        myLightNode->attachObject(myLight);

        aSceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    }

    Ogre::Vector3f SceneBuilder::buildMap(Ogre::SceneManager *aSceneManager, const ServerData &aServerData)
    {
        const auto myMapSize = aServerData._mapSize;
        const constexpr int myTileSize = 1;
        Ogre::Vector3f myCenterPos(0, 0, 0);

        for (unsigned int i = 0; i < myMapSize.first; i++) {
            for (unsigned int j = 0; j < myMapSize.second; j++) {
                const std::string myName = std::to_string(i) + " " + std::to_string(j);

                SceneBuilder::createTile(aSceneManager, Ogre::Vector2(static_cast<float>(i), static_cast<float>(j)),
                                         myName);
            }
        }
        myCenterPos.x = (static_cast<float>(myMapSize.first) / 2) * (myTileSize * MAP_OFFSET);
        myCenterPos.z = (static_cast<float>(myMapSize.second) / 2) * (myTileSize * MAP_OFFSET);
        return myCenterPos;
    }

    cameraReturn SceneBuilder::buildCamera(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenterPos,
                                           Ogre::RenderWindow *aRenderWindow, App &aApp)
    {
        const auto myMapSize = aApp.getServerData()._mapSize;
        const constexpr float myBaseRadius = 15;
        const constexpr int myClipDistance = 5;
        const float myRadius = myBaseRadius * (static_cast<float>(std::max(myMapSize.first, myMapSize.second)) / 3);
        Ogre::Vector3 myCamPos(aCenterPos.x, aCenterPos.y + myRadius + myClipDistance, aCenterPos.z + myRadius);

        Ogre::SceneNode *myCamNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);

        Ogre::Camera *myCam = aSceneManager->createCamera(CAMERA_NAME);
        myCam->setNearClipDistance(myClipDistance);
        myCam->setAutoAspectRatio(true);

        myCamNode->attachObject(myCam);
        myCamNode->lookAt(aCenterPos, Ogre::Node::TS_WORLD);

        if (aRenderWindow != nullptr) {
            auto *myCameraHandler = new CameraHandler(myCamNode, aCenterPos, myRadius, aApp);
            auto *myClickHandler = new ClickHandler(myCamNode, aRenderWindow, aSceneManager, aApp);

            aApp.addInputListener(myCameraHandler);
            aApp.addInputListener(myClickHandler);

            aRenderWindow->addViewport(myCam);
            return {myCameraHandler, myClickHandler};
        }
        return {nullptr, nullptr};
    }

    void SceneBuilder::buildConnectedPlayersAndEggs(Ogre::SceneManager *aSceneManager, const ServerData &aServerData)
    {
        auto myPlayerData = aServerData._players;
        auto myEggData = aServerData._eggs;

        for (const auto &myPlayer : myPlayerData) {
            SceneBuilder::createPlayer(aSceneManager, myPlayer);
        }
        for (const auto &myEgg : myEggData) {
            SceneBuilder::createEgg(aSceneManager, myEgg);
        }
    }

    void SceneBuilder::createTile(Ogre::SceneManager *aSceneManager, const Ogre::Vector2 &aPosition,
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

    void SceneBuilder::createPlayer(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayerData)
    {
        static const constexpr Ogre::Real myScale = 0.5F;
        const std::string myPlayerName = PLAYER_PREFIX_NAME + aPlayerData.getId();

        try {
            Ogre::Entity *myEntity = aSceneManager->createEntity(myPlayerName, PLAYER_MODEL_NAME);
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myPlayerName);

            myNode->attachObject(myEntity);
            myNode->setScale(myScale, myScale, myScale);

            SceneBuilder::setPlayerPosAndOrientation(aSceneManager, aPlayerData);
        } catch (Ogre::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void SceneBuilder::createEgg(Ogre::SceneManager *aSceneManager, const EggData &aEggData)
    {
        static const constexpr Ogre::Real myScale = 0.5F;
        static const constexpr int myAngle = 90;
        const std::string myEggName = EGG_PREFIX_NAME + std::to_string(aEggData.getId());

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

    std::pair<float, float> SceneBuilder::createText(const std::string &aOverlayName, const std::string &aText,
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

    std::pair<float, float> SceneBuilder::calculateDimensions(const std::string &aButtonText)
    {
        Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().getByName(FONT_NAME, RESSOURCE_GROUP_NAME);
        const float myCharHeight = myFont->getGlyphAspectRatio('A') * 17;
        float myTextWidth = 0;
        const constexpr float myPaddingX = 1.05F;
        const constexpr float myPaddingY = 1.5F;

        myTextWidth = myCharHeight * static_cast<float>(aButtonText.size()) * myPaddingX;
        return {myTextWidth, static_cast<int>(myCharHeight * myPaddingY)};
    }

    void SceneBuilder::setPlayerPosAndOrientation(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayer)
    {
        const auto &myPlayerId = PLAYER_PREFIX_NAME + aPlayer.getId();
        static const std::unordered_map<Orientation, Ogre::Real> myOrientationMap = {{Orientation::NORTH, 180},
                                                                                     {Orientation::EAST, 90},
                                                                                     {Orientation::SOUTH, 0},
                                                                                     {Orientation::WEST, 270}};
        Ogre::SceneNode *myNode = aSceneManager->getSceneNode(myPlayerId);

        myNode->setPosition(static_cast<float>(aPlayer.getPosition().first * MAP_OFFSET), PLAYER_Y_POS,
                            static_cast<float>(aPlayer.getPosition().second * MAP_OFFSET));
        myNode->setOrientation(
            Ogre::Quaternion(Ogre::Degree(myOrientationMap.at(aPlayer.getOrientation())), Ogre::Vector3::UNIT_Y));
    }

} // namespace Zappy::GUI
