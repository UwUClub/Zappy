/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#include "App.hpp"
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreInput.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <algorithm>
#include <memory>
#include "CameraHandler.hpp"
#include "Constexpr.hpp"
#include "FrameHandler.hpp"
#include "InputHandler.hpp"
#include "PlayerData.hpp"
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    App::App(Zappy::GUI::ClientApi &client, const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          _client(client),
          _cameraHandler(nullptr),
          _frameHandler(nullptr),
          _clickHandler(nullptr)
    {
        this->initApp();
        _client.registerSubscriber(*this);

        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager("DefaultSceneManager", SCENE_MAN_NAME);
        Ogre::RTShader::ShaderGenerator *myShadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        _frameHandler = std::make_unique<FrameHandler>(myScnMgr, _client);

        myShadergen->addSceneManager(myScnMgr);
        this->setupLight(myScnMgr);
        auto nodeCenterPos = this->setupMap(myScnMgr);
        this->setupCamera(myScnMgr, nodeCenterPos);
        myRoot->addFrameListener(_frameHandler.get());
    }

    App::~App()
    {
        this->closeApp();
        _client.disconnect();
    }

    void App::setupLight(Ogre::SceneManager *aSceneManager)
    {
        const constexpr double myRGB = 1.0;
        aSceneManager->setAmbientLight(Ogre::ColourValue(myRGB, myRGB, myRGB));
        // Ogre::Light *light = scnMgr->createLight("MainLight");
        // Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        // lightNode->setPosition(0, 10, 15);
        // lightNode->attachObject(light);
    }

    void App::setupCamera(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenterPos)
    {
        auto myServerData = _client.getServerData();
        const auto myMapSize = myServerData._mapSize;
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

        auto *myRenderWindow = this->getRenderWindow();
        if (myRenderWindow != nullptr) {
            _cameraHandler = std::make_unique<CameraHandler>(myCamNode, aCenterPos, myRadius, _client);
            _clickHandler = std::make_unique<ClickHandler>(myCamNode, myRenderWindow, aSceneManager, _client);
            this->addInputListener(_cameraHandler.get());
            this->addInputListener(_clickHandler.get());

            myRenderWindow->addViewport(myCam);
        }
    }

    Ogre::Vector3f App::setupMap(Ogre::SceneManager *aSceneManager)
    {
        auto myServerData = _client.getServerData();
        const auto myMapSize = myServerData._mapSize;
        std::cout << "Map size: " << myMapSize.first << " " << myMapSize.second << std::endl;
        const constexpr int myTileSize = 1;

        Ogre::Vector3f myCenterPos(0, 0, 0);
        for (unsigned int i = 0; i < myMapSize.first; i++) {
            for (unsigned int j = 0; j < myMapSize.second; j++) {
                std::string name = std::to_string(i) + " " + std::to_string(j);
                Ogre::Entity *myEntity = aSceneManager->createEntity(name, "Sinbad.mesh");
                Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(name);
                myNode->attachObject(myEntity);
                myNode->setPosition(static_cast<float>(i) * (myTileSize * MAP_OFFSET), 0,
                                    static_cast<float>(j) * (myTileSize * MAP_OFFSET));
            }
        }
        myCenterPos.x = (static_cast<float>(myMapSize.first) / 2) * (myTileSize * MAP_OFFSET);
        myCenterPos.z = (static_cast<float>(myMapSize.second) / 2) * (myTileSize * MAP_OFFSET);
        return myCenterPos;
    }

    void App::getNotified(std::string &aNotification)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        if (aNotification.find("pnw") != std::string::npos) {
            _client.parseServerResponses();
            auto myNewPlayer = _client.getServerData()._players.back();
            this->addPlayer(myNewPlayer, myScnMgr);
            return;
        }
        if (aNotification.find("pdi") != std::string::npos) {
            int myIndex = std::stoi(aNotification.substr(4));
            this->removePlayer(myIndex, myScnMgr);
            _client.parseServerResponses();
            return;
        }
        // _client.parseServerResponses();
    }

    void App::addPlayer(PlayerData &aPlayer, Ogre::SceneManager *aSceneManager)
    {
        static const std::unordered_map<Orientation, Ogre::Real> myOrientationMap = {{Orientation::SOUTH, 0},
                                                                                     {Orientation::EAST, 90},
                                                                                     {Orientation::NORTH, 180},
                                                                                     {Orientation::WEST, 270}};
        auto myServerData = _client.getServerData();
        const auto &myPlayerId = aPlayer.getId();

        Ogre::Entity *myEntity = aSceneManager->createEntity(myPlayerId, "Sinbad.mesh");
        Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myPlayerId);

        myNode->attachObject(myEntity);
        myNode->setPosition(static_cast<float>(aPlayer.getPosition().first * MAP_OFFSET), NEW_PLAYER_Y_POS,
                            static_cast<float>(aPlayer.getPosition().second * MAP_OFFSET));
        myNode->setOrientation(
            Ogre::Quaternion(Ogre::Degree(myOrientationMap.at(aPlayer.getOrientation())), Ogre::Vector3::UNIT_Y));
    }

    void App::removePlayer(int aIndex, Ogre::SceneManager *aSceneManager)
    {
        auto myServerData = _client.getServerData();
        auto myPlayerId = std::to_string(aIndex);

        aSceneManager->destroyEntity(std::to_string(aIndex));
    }
} // namespace Zappy::GUI
