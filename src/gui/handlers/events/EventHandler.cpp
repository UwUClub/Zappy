/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraHandler
*/

#include "EventHandler.hpp"
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreMath.h>
#include <OgreCamera.h>
#include <OgreCommon.h>
#include <OgreRay.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <iostream>
#include <memory>
#include "MouseHandler.hpp"

namespace Zappy::GUI {

    EventHandler::EventHandler(Ogre::SceneNode *aCameraNode, Ogre::Vector3 aCenter, Ogre::Real aRadius,
                               Ogre::SceneManager &aSeneManager, Ogre::RenderWindow *aRenderWindow)
        : _isShiftPressed(false),
          _cameraNode(aCameraNode),
          _cameraPositionBase(aCameraNode->getPosition()),
          _center(aCenter),
          _radius(aRadius),
          _radiusBase(aRadius),
          _inclination(Ogre::Degree(BASE_INCLINATION)),
          _azimuth(Ogre::Degree(BASE_AZIMUTH)),
          _sceneManager(aSeneManager),
          _renderWindow(aRenderWindow)
    {}

    EventHandler::~EventHandler() = default;

    bool EventHandler::mouseMoved(const OgreBites::MouseMotionEvent &aEvt)
    {
        const constexpr float myMouseSensitivity = 0.1F;

        if (_isLeftClickPressed && _isShiftPressed) {
            _inclination += Ogre::Degree(-static_cast<float>(aEvt.yrel) * myMouseSensitivity);
            _azimuth -= Ogre::Degree(-static_cast<float>(aEvt.xrel) * myMouseSensitivity);

            updateCameraPosition();
            return true;
        }
        if (_isRightClickPressed) {
            // move camera on X and Z axis
        }
        return true;
    }

    bool EventHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
    {
        MouseHandler::mousePressed(aEvt);

        if (_isLeftClickPressed && !_isShiftPressed) {
            auto *myNode = getNodeUnderMouse(Ogre::Vector2(static_cast<float>(aEvt.x), static_cast<float>(aEvt.y)));
            if (myNode != nullptr) {
                // open inventory window
            }
            return true;
        }
        return true;
    }

    bool EventHandler::mouseReleased(const OgreBites::MouseButtonEvent &aEvt)
    {
        MouseHandler::mouseReleased(aEvt);
        return true;
    }

    bool EventHandler::mouseWheelRolled(const OgreBites::MouseWheelEvent &aEvt)
    {
        const constexpr float myZoomPower = 10.0F;
        const constexpr float myRadMax = 1000.0F;
        const constexpr float myRadMin = 10.0F;

        _radius += -static_cast<float>(aEvt.y) * myZoomPower;

        _radius = Ogre::Math::Clamp<Ogre::Real>(_radius, myRadMin, myRadMax);

        updateCameraPosition();
        return true;
    }

    bool EventHandler::keyPressed(const OgreBites::KeyboardEvent &aEvt)
    {
        if (aEvt.keysym.sym == OgreBites::SDLK_SPACE) {
            _radius = _radiusBase;
            _inclination = Ogre::Degree(BASE_INCLINATION);
            _azimuth = Ogre::Degree(BASE_AZIMUTH);
            _cameraNode->setPosition(_cameraPositionBase);
            _cameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
            _cameraNode->lookAt(_center, Ogre::Node::TS_PARENT);
        }
        if (aEvt.keysym.sym == OgreBites::SDLK_LSHIFT) {
            _isShiftPressed = true;
        }
        return true;
    }

    bool EventHandler::keyReleased(const OgreBites::KeyboardEvent &aEvt)
    {
        if (aEvt.keysym.sym == OgreBites::SDLK_LSHIFT) {
            _isShiftPressed = false;
        }
        if (aEvt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true;
    }

    void EventHandler::updateCameraPosition()
    {
        Ogre::Real mySinInclination = Ogre::Math::Sin(_inclination);
        Ogre::Real myCosInclination = Ogre::Math::Cos(_inclination);
        Ogre::Real mySinAzimuth = Ogre::Math::Sin(_azimuth);
        Ogre::Real myCosAzimuth = Ogre::Math::Cos(_azimuth);

        Ogre::Vector3 position =
            _center
            + _radius
                  * Ogre::Vector3(mySinInclination * myCosAzimuth, myCosInclination, mySinInclination * mySinAzimuth);

        _cameraNode->setPosition(position);
        _cameraNode->lookAt(_center, Ogre::Node::TS_PARENT);
    }

    Ogre::SceneNode *EventHandler::getNodeUnderMouse(const Ogre::Vector2 &mousePos)
    {
        Ogre::Camera *myCamera = reinterpret_cast<Ogre::Camera *>(_cameraNode->getAttachedObject("MainCamera"));
        if (myCamera == nullptr) {
            std::cout << "Camera not found" << std::endl;
            return nullptr;
        }
        Ogre::Ray mouseRay =
            myCamera->getCameraToViewportRay(mousePos.x / static_cast<float>(_renderWindow->getWidth()),
                                             mousePos.y / static_cast<float>(_renderWindow->getHeight()));
        Ogre::RaySceneQuery *raySceneQuery = _sceneManager.createRayQuery(mouseRay);
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
