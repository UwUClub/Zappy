/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ClickHandler
*/

#include "ClickHandler.hpp"
#include <OgreScriptCompiler.h>
#include <iostream>

namespace Zappy::GUI {
    ClickHandler::ClickHandler(Ogre::SceneNode *aCameraNode, Ogre::RenderWindow *aRenderWindow,
                               Ogre::SceneManager *aSceneManager)
        : _cameraNode(aCameraNode),
          _renderWindow(aRenderWindow),
          _sceneManager(aSceneManager)
    {}

    ClickHandler::~ClickHandler() = default;

    bool ClickHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
    {
        InputHandler::mousePressed(aEvt);

        if (_isLeftClickPressed && !_isShiftPressed) {
            auto *myNode = getNodeUnderMouse(Ogre::Vector2(static_cast<float>(aEvt.x), static_cast<float>(aEvt.y)));
            if (myNode != nullptr) {
                // display inventory
                myNode->showBoundingBox(!myNode->getShowBoundingBox());
            }
            return true;
        }
        return true;
    }

    Ogre::SceneNode *ClickHandler::getNodeUnderMouse(const Ogre::Vector2 &mousePos)
    {
        Ogre::Camera *myCamera = reinterpret_cast<Ogre::Camera *>(_cameraNode->getAttachedObject("MainCamera"));
        if (myCamera == nullptr) {
            std::cout << "Camera not found" << std::endl;
            return nullptr;
        }
        Ogre::Ray mouseRay =
            myCamera->getCameraToViewportRay(mousePos.x / static_cast<float>(_renderWindow->getWidth()),
                                             mousePos.y / static_cast<float>(_renderWindow->getHeight()));
        Ogre::RaySceneQuery *raySceneQuery = _sceneManager->createRayQuery(mouseRay);
        raySceneQuery->setSortByDistance(true);

        Ogre::RaySceneQueryResult &result = raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator itr;

        for (itr = result.begin(); itr != result.end(); itr++) {
            if ((itr->movable != nullptr) && (itr->movable->getParentSceneNode() != nullptr)) {
                Ogre::SceneNode *node = itr->movable->getParentSceneNode();
                return node;
            }
        }

        return nullptr; // Return null if no node found
    }
} // namespace Zappy::GUI