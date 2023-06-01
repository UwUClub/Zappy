#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreInput.h>
#include <OgrePrerequisites.h>
#include <OgreRoot.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "CameraHandler.hpp"
#include "ClientApi.hpp"
#include "EventHandler.hpp"
#include "FrameHandler.hpp"
#include "ParserData.hpp"

int main(int argc, char **argv)
{
    // try {
    // Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
    //     parserData.parseData(argc, argv);
    //     Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "team_name");
    //     myClientApi.joinGame();
    //     while (true) {
    //         if (myClientApi.update() >= 1) {
    //             break;
    //         }
    //     }
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // }
    OgreBites::ApplicationContext ctx("Zappy");
    ctx.initApp();
    Ogre::Root *root = ctx.getRoot();
    Ogre::SceneManager *scnMgr = root->createSceneManager();
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    Ogre::Light *light = scnMgr->createLight("MainLight");
    Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);
    Ogre::SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    Ogre::Camera *cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    Ogre::Entity *ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    camNode->lookAt(node->_getDerivedPosition(), Ogre::Node::TS_WORLD);
    ctx.getRenderWindow()->addViewport(cam);
    Zappy::GUI::EventHandler eventHandler;
    Zappy::GUI::CameraHandler cameraHandler(camNode, node->getPosition(), 15);
    Zappy::GUI::FrameHandler frameHandler;
    ctx.addInputListener(&eventHandler);
    ctx.addInputListener(&cameraHandler);
    root->addFrameListener(&frameHandler);
    ctx.getRoot()->startRendering();
    ctx.closeApp();
    return 0;
}
