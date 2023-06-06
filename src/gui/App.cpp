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
<<<<<<< HEAD
#include <algorithm>
    == == == =
>>>>>>> dev
#include <memory>
#include "CameraHandler.hpp"
#include "FrameHandler.hpp"
#include "InputHandler.hpp"
#include "ServerData.hpp"

    namespace Zappy::GUI
{
    App::App(Zappy::GUI::ClientApi & client, const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          _client(client),
          _cameraHandler(nullptr),
          _frameHandler(nullptr),
          _clickHandler(nullptr)
    {
        this->initApp();
        _client.registerSubscriber(*this);

        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager();
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

    void App::setupLight(Ogre::SceneManager * aSceneManager)
    {
        const constexpr double myRGB = 1.0;
        aSceneManager->setAmbientLight(Ogre::ColourValue(myRGB, myRGB, myRGB));
        // Ogre::Light *light = scnMgr->createLight("MainLight");
        // Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        // lightNode->setPosition(0, 10, 15);
        // lightNode->attachObject(light);
    }

    void App::setupCamera(Ogre::SceneManager * aSceneManager, Ogre::Vector3 & aCenterPos)
    {
<<<<<<< HEAD
        auto myServerData = _client.getServerData();
        const auto myMapSize = myServerData._mapSize;
        const constexpr float myBaseRadius = 15;
        const constexpr int myClipDistance = 5;
        const float myRadius = myBaseRadius * (static_cast<float>(std::max(myMapSize.first, myMapSize.second)) / 3);
=======
        const constexpr int myRadius = 15 * (10 / 3);
        const constexpr int myClipDistance = 5;
>>>>>>> dev
        Ogre::Vector3 myCamPos(aCenterPos.x, aCenterPos.y + myRadius + myClipDistance, aCenterPos.z + myRadius);

        Ogre::SceneNode *myCamNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);

        Ogre::Camera *myCam = aSceneManager->createCamera("MainCamera");
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

    Ogre::Vector3f App::setupMap(Ogre::SceneManager * aSceneManager)
    {
        auto myServerData = _client.getServerData();
        const auto myMapSize = myServerData._mapSize;
        const constexpr int myTileSize = 1;
        const constexpr int myOffset = 5;

        Ogre::Vector3f myCenterPos(0, 0, 0);
        for (unsigned int i = 0; i < myMapSize.first; i++) {
            for (unsigned int j = 0; j < myMapSize.second; j++) {
                std::string name = std::to_string(i) + " " + std::to_string(j);
                Ogre::Entity *myEntity = aSceneManager->createEntity(name, "Sinbad.mesh");
                Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(name);
                myNode->attachObject(myEntity);
                myNode->setPosition(static_cast<float>(i) * (myTileSize * myOffset), 0,
                                    static_cast<float>(j) * (myTileSize * myOffset));
            }
        }
        // get the middle tile position to center the camera
        myCenterPos.x = (static_cast<float>(myMapSize.first) / 2) * (myTileSize * myOffset);
        myCenterPos.z = (static_cast<float>(myMapSize.second) / 2) * (myTileSize * myOffset);
        return myCenterPos;
    }

    void App::getNotified(std::string & aNotification)
    {
        std::cout << "App: " << aNotification << std::endl;
        _client.parseServerResponses();
    }
} // namespace Zappy::GUI
