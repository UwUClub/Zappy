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
#include "CameraHandler.hpp"
#include "EventHandler.hpp"
#include "FrameHandler.hpp"

namespace Zappy::GUI {
    App::App(const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          _cameraHandler(nullptr)
    //   _client(std::move(client)),
    {
        this->initApp();

        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager();
        Ogre::RTShader::ShaderGenerator *myShadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

        // _client->joinGame();

        myShadergen->addSceneManager(myScnMgr);
        this->setupLight(*myScnMgr);
        auto nodeCenterPos = this->setupMap(*myScnMgr);
        this->setupCamera(*myScnMgr, nodeCenterPos);
        myRoot->addFrameListener(&_frameHandler);
        this->addInputListener(&_eventHandler);
    }

    App::~App()
    {
        this->closeApp();
        delete _cameraHandler;
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

    // todo: handle dynamic setup camera
    void App::setupCamera(Ogre::SceneManager &aSceneManager, Ogre::Vector3 &aCenterPos)
    {
        const constexpr int myRadius = 15;
        const constexpr int myClipDistance = 5;
        Ogre::Vector3 myCamPos(0, 0, myRadius);

        Ogre::SceneNode *myCamNode = aSceneManager.getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);
        myCamNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        Ogre::Camera *myCam = aSceneManager.createCamera("MainCamera");
        myCam->setNearClipDistance(myClipDistance);
        myCam->setAutoAspectRatio(true);

        myCamNode->attachObject(myCam);
        myCamNode->lookAt(aCenterPos, Ogre::Node::TS_WORLD);

        _cameraHandler = new CameraHandler(myCamNode, aCenterPos, myRadius);
        this->addInputListener(_cameraHandler);

        auto *myRenderWindow = this->getRenderWindow();
        if (myRenderWindow != nullptr) {
            myRenderWindow->addViewport(myCam);
        }
    }

    Ogre::Vector3f App::setupMap(Ogre::SceneManager &aSceneManager)
    {
        Ogre::Entity *tile = aSceneManager.createEntity("Sinbad.mesh");
        Ogre::SceneNode *node = aSceneManager.getRootSceneNode()->createChildSceneNode();

        node->attachObject(tile);
        return node->getPosition();
    }
} // namespace Zappy::GUI
