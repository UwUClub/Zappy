/*
** EPITECH PROJECT, 2023
** zap
** File description:
** SceneBuilder
*/

#include "SceneBuilder.hpp"
#include <OgreEntity.h>
#include <OgrePrerequisites.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "App.hpp"
#include "CameraHandler.hpp"
#include "ClickHandler.hpp"
#include "Constexpr.hpp"
#include "ElementFactory.hpp"
#include "OGRE/OgreRenderWindow.h"
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

                ElementFactory::createTile(aSceneManager, Ogre::Vector2(static_cast<float>(i), static_cast<float>(j)),
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
            ElementFactory::createPlayer(aSceneManager, myPlayer);
        }
        for (const auto &myEgg : myEggData) {
            ElementFactory::createEgg(aSceneManager, myEgg);
        }
    }
} // namespace Zappy::GUI
