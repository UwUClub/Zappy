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
#include "EventHandler.hpp"
#include "FrameHandler.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    App::App(const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          _cameraHandler(nullptr),
          _frameHandler(nullptr)

    //   _client(std::move(client)),
    {
        this->initApp();

        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager();
        Ogre::RTShader::ShaderGenerator *myShadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        _frameHandler = new FrameHandler(*myScnMgr);

        myShadergen->addSceneManager(myScnMgr);
        this->setupLight(*myScnMgr);
        auto nodeCenterPos = this->setupMap(*myScnMgr);
        this->setupCamera(*myScnMgr, nodeCenterPos);
        myRoot->addFrameListener(_frameHandler);
    }

    App::~App()
    {
        this->closeApp();
        delete _cameraHandler;
        delete _frameHandler;
    }

    void App::setupLight(Ogre::SceneManager &aSceneManager)
    {
        const constexpr double myRGB = 1.0;
        aSceneManager.setAmbientLight(Ogre::ColourValue(myRGB, myRGB, myRGB));
        // Ogre::Light *light = scnMgr->createLight("MainLight");
        // Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        // lightNode->setPosition(0, 10, 15);
        // lightNode->attachObject(light);
    }

    void App::setupCamera(Ogre::SceneManager &aSceneManager, Ogre::Vector3 &aCenterPos)
    {
        const constexpr int myRadius = 15;
        const constexpr int myClipDistance = 5;
        Ogre::Vector3 myCamPos(aCenterPos.x, aCenterPos.y + myRadius + myClipDistance, aCenterPos.z + myRadius);

        Ogre::SceneNode *myCamNode = aSceneManager.getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);

        Ogre::Camera *myCam = aSceneManager.createCamera("MainCamera");
        myCam->setNearClipDistance(myClipDistance);
        myCam->setAutoAspectRatio(true);

        myCamNode->attachObject(myCam);
        myCamNode->lookAt(aCenterPos, Ogre::Node::TS_WORLD);

        auto *myRenderWindow = this->getRenderWindow();
        if (myRenderWindow != nullptr) {
            _cameraHandler = new EventHandler(myCamNode, aCenterPos, myRadius, aSceneManager, myRenderWindow);
            this->addInputListener(_cameraHandler);

            myRenderWindow->addViewport(myCam);
        }
    }

    Ogre::Vector3f App::setupMap(Ogre::SceneManager &aSceneManager)
    {
        const constexpr int myMapSize = 10;
        const constexpr int myTileSize = 1;
        const constexpr int myOffset = 1;

        Ogre::Vector3f myCenterPos(0, 0, 0);
        for (int i = 0; i < myMapSize; i++) {
            for (int j = 0; j < myMapSize; j++) {
                std::string name = std::to_string(i) + " " + std::to_string(j);
                Ogre::Entity *myEntity = aSceneManager.createEntity(name, "Sinbad.mesh");
                Ogre::SceneNode *myNode = aSceneManager.getRootSceneNode()->createChildSceneNode(name);
                myNode->attachObject(myEntity);
                myNode->setPosition(static_cast<float>(i) * (myTileSize * myOffset), 0,
                                    static_cast<float>(j) * (myTileSize * myOffset));
            }
        }
        // get the middle tile position to center the camera
        myCenterPos.x = (myMapSize / 2) * (myTileSize * myOffset);
        myCenterPos.z = (myMapSize / 2) * (myTileSize * myOffset);
        return myCenterPos;
    }
} // namespace Zappy::GUI
