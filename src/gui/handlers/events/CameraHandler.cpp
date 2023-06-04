/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraHandler
*/

#include "CameraHandler.hpp"
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
#include "InputHandler.hpp"

namespace Zappy::GUI {

    CameraHandler::CameraHandler(Ogre::SceneNode *aCameraNode, Ogre::Vector3 aCenter, Ogre::Real aRadius)
        : _cameraNode(aCameraNode),
          _cameraPositionBase(aCameraNode->getPosition()),
          _center(aCenter),
          _radius(aRadius),
          _radiusBase(aRadius),
          _inclination(Ogre::Degree(BASE_INCLINATION)),
          _azimuth(Ogre::Degree(BASE_AZIMUTH))
    {}

    CameraHandler::~CameraHandler() = default;

    bool CameraHandler::mouseMoved(const OgreBites::MouseMotionEvent &aEvt)
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

    bool CameraHandler::mouseWheelRolled(const OgreBites::MouseWheelEvent &aEvt)
    {
        const constexpr float myZoomPower = 10.0F;
        const constexpr float myRadMax = 1000.0F;
        const constexpr float myRadMin = 10.0F;

        _radius += -static_cast<float>(aEvt.y) * myZoomPower;

        _radius = Ogre::Math::Clamp<Ogre::Real>(_radius, myRadMin, myRadMax);

        updateCameraPosition();
        return true;
    }

    bool CameraHandler::keyPressed(const OgreBites::KeyboardEvent &aEvt)
    {
        InputHandler::keyPressed(aEvt);

        if (aEvt.keysym.sym == OgreBites::SDLK_SPACE) {
            _radius = _radiusBase;
            _inclination = Ogre::Degree(BASE_INCLINATION);
            _azimuth = Ogre::Degree(BASE_AZIMUTH);
            _cameraNode->setPosition(_cameraPositionBase);
            _cameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
            _cameraNode->lookAt(_center, Ogre::Node::TS_PARENT);
        }
        return true;
    }

    void CameraHandler::updateCameraPosition()
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
} // namespace Zappy::GUI
