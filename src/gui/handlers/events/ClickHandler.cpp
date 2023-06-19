/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ClickHandler
*/

#include "ClickHandler.hpp"
#include <OgreScriptCompiler.h>
#include <iostream>
#include <vector>
#include "App.hpp"
#include "Button.hpp"
#include "Constexpr.hpp"
#include "Inventory.hpp"

namespace Zappy::GUI {
    ClickHandler::ClickHandler(Ogre::SceneNode *aCameraNode, Ogre::RenderWindow *aRenderWindow,
                               Ogre::SceneManager *aSceneManager, App &aApp)
        : InputHandler(aApp),
          _cameraNode(aCameraNode),
          _renderWindow(aRenderWindow),
          _sceneManager(aSceneManager),
          _buttons(aApp.getButtons()),
          _app(aApp)
    {}

    ClickHandler::~ClickHandler() = default;

    bool ClickHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
    {
        InputHandler::mousePressed(aEvt);

        if (_isLeftClickPressed && !_isShiftPressed) {
            if (execButton(Ogre::Vector2(static_cast<float>(aEvt.x), static_cast<float>(aEvt.y)))) {
                return true;
            }

            auto *myNode = getNodeUnderMouse(Ogre::Vector2(static_cast<float>(aEvt.x), static_cast<float>(aEvt.y)));
            if (myNode->getName().find("Player_") != std::string::npos) {
                myNode->showBoundingBox(!myNode->getShowBoundingBox());
                try {
                    Inventory myInventory;
                    int myId = myInventory.parsePlayer(myNode->getName());
                    myInventory.displayPlayerInventory(myId, _app);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                return true;
            } else {
                std::cout << "Node not found" << std::endl;
            }
            return true;
        }
        return true;
    }

    bool ClickHandler::execButton(const Ogre::Vector2 &mousePos)
    {
        for (auto &button : _buttons) {
            if (button->isOnButton(mousePos)) {
                button->onClick();
                return true;
            }
        }
        return false;
    }

    Ogre::SceneNode *ClickHandler::getNodeUnderMouse(const Ogre::Vector2 &aMousePos)
    {
        auto *myCamera = reinterpret_cast<Ogre::Camera *>(_cameraNode->getAttachedObject(CAMERA_NAME));
        if (myCamera == nullptr) {
            std::cerr << "Camera not found" << std::endl;
            return nullptr;
        }

        Ogre::Ray myMouseRay =
            myCamera->getCameraToViewportRay(aMousePos.x / static_cast<float>(_renderWindow->getWidth()),
                                             aMousePos.y / static_cast<float>(_renderWindow->getHeight()));
        Ogre::RaySceneQuery *myRaySceneQuery = _sceneManager->createRayQuery(myMouseRay);

        myRaySceneQuery->setSortByDistance(true);

        Ogre::RaySceneQueryResult &myResult = myRaySceneQuery->execute();

        for (const auto &myItr : myResult) {
            if ((myItr.movable != nullptr) && (myItr.movable->getParentSceneNode() != nullptr)) {
                Ogre::SceneNode *node = myItr.movable->getParentSceneNode();
                return node;
            }
        }

        return nullptr; // Return null if no node found
    }
} // namespace Zappy::GUI