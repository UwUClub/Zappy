/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraHandler
*/

#include "CameraHandler.hpp"
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreMath.h>
#include <iostream>

namespace Zappy::GUI {

    CameraHandler::CameraHandler(Ogre::SceneNode *aCameraNode, Ogre::Vector3 aCenter, Ogre::Real aRadius)
        : _isLeftClickPressed(false),
          _isRightClickPressed(false),
          _cameraNode(aCameraNode),
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
        if (_isLeftClickPressed || _isRightClickPressed) {
            _inclination += Ogre::Degree(-aEvt.yrel * 0.1f);
            _azimuth -= Ogre::Degree(-aEvt.xrel * 0.1f);

            updateCameraPosition();
        }
        return true;
    }

    bool CameraHandler::mousePressed(const OgreBites::MouseButtonEvent &aEvt)
    {
        if (aEvt.button == OgreBites::BUTTON_RIGHT) {
            _isRightClickPressed = true;
        } else if (aEvt.button == OgreBites::BUTTON_LEFT) {
            _isLeftClickPressed = true;
        }
        return true;
    }

    bool CameraHandler::mouseReleased(const OgreBites::MouseButtonEvent &aEvt)
    {
        if (aEvt.button == OgreBites::BUTTON_RIGHT) {
            _isRightClickPressed = false;
        } else if (aEvt.button == OgreBites::BUTTON_LEFT) {
            _isLeftClickPressed = false;
        }
        return true;
    }

    bool CameraHandler::mouseWheelRolled(const OgreBites::MouseWheelEvent &aEvt)
    {
        _radius += -aEvt.y * 10.0f;

        _radius = Ogre::Math::Clamp<Ogre::Real>(_radius, 10.0f, 1000.0f);

        updateCameraPosition();
        return true;
    }

    bool CameraHandler::keyPressed(const OgreBites::KeyboardEvent &aEvt)
    {
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
