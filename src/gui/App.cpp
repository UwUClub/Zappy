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
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <algorithm>
#include <functional>
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
        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager("DefaultSceneManager", SCENE_MAN_NAME);

        this->instantiateApp();
        _client.registerSubscriber(*this);

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

    void App::instantiateApp()
    {
        try {
            auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem", "Zappy");
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Zappy");
            myScnMgr->createEntity("Sinbad.mesh");
            myScnMgr->createEntity("Egg.mesh");

        } catch (const Ogre::Exception &e) {
            throw AppException(e.what());
        }
    }

    void App::setupLight(Ogre::SceneManager *aSceneManager)
    {
        const constexpr double myRGB = 1.0;
        const constexpr int myLightX = 0;
        const constexpr int myLightY = 50;
        const constexpr int myLightZ = 15;
        Ogre::Light *light = aSceneManager->createLight("MainLight");
        Ogre::SceneNode *lightNode = aSceneManager->getRootSceneNode()->createChildSceneNode();

        aSceneManager->setAmbientLight(Ogre::ColourValue(myRGB, myRGB, myRGB));
        lightNode->setPosition(myLightX, myLightY, myLightZ);
        lightNode->attachObject(light);
    }

    void App::setupCamera(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenterPos)
    {
        auto myServerData = _client.getServerData();
        const auto myMapSize = myServerData._mapSize;
        const constexpr float myBaseRadius = 15;
        const constexpr int myClipDistance = 5;
        const float myRadius = myBaseRadius * (static_cast<float>(std::max(myMapSize.first, myMapSize.second)) / 3);
        Ogre::Vector3 myCamPos(aCenterPos.x, aCenterPos.y + myRadius + myClipDistance, aCenterPos.z + myRadius);
        auto *myRenderWindow = this->getRenderWindow();

        Ogre::SceneNode *myCamNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);

        Ogre::Camera *myCam = aSceneManager->createCamera(CAMERA_NAME);
        myCam->setNearClipDistance(myClipDistance);
        myCam->setAutoAspectRatio(true);

        myCamNode->attachObject(myCam);
        myCamNode->lookAt(aCenterPos, Ogre::Node::TS_WORLD);

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
        const constexpr int myTileSize = 1;
        const constexpr Ogre::Real myScale = 0.05F;
        Ogre::Vector3f myCenterPos(0, 0, 0);

        for (unsigned int i = 0; i < myMapSize.first; i++) {
            for (unsigned int j = 0; j < myMapSize.second; j++) {
                std::string myName = std::to_string(i) + " " + std::to_string(j);

                try {
                    Ogre::Entity *myEntity = aSceneManager->createEntity(myName, "Rock.mesh");
                    Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myName);

                    myNode->attachObject(myEntity);
                    myNode->setPosition(static_cast<float>(i) * (myTileSize * MAP_OFFSET), 0,
                                        static_cast<float>(j) * (myTileSize * MAP_OFFSET));
                    myNode->setScale(myScale, myScale, myScale);
                } catch (Ogre::Exception &e) {
                    std::cerr << e.what() << std::endl;
                    return myCenterPos;
                }
            }
        }
        myCenterPos.x = (static_cast<float>(myMapSize.first) / 2) * (myTileSize * MAP_OFFSET);
        myCenterPos.z = (static_cast<float>(myMapSize.second) / 2) * (myTileSize * MAP_OFFSET);
        return myCenterPos;
    }

    void App::setTime(int aTime)
    {
        std::string myCommand = "sst " + std::to_string(aTime);

        _client.sendCommand(myCommand);
    }
} // namespace Zappy::GUI
