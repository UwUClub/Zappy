/*
** EPITECH PROJECT, 2023
** zap
** File description:
** MovementHandler
*/

#include "MovementHandler.hpp"
#include <OgreSceneNode.h>
#include <iostream>
#include "Constexpr.hpp"

namespace Zappy::GUI {
    MovementHandler::MovementHandler(Ogre::Entity *aEntity, const std::pair<int, int> &aMapSize)
        : _entity(aEntity),
          _arrivalPoint(Ogre::Vector3::ZERO),
          _distance(0),
          _mapSize(aMapSize),
          _willTeleport(false)
    {}

    MovementHandler::~MovementHandler() = default;

    void MovementHandler::setArrivalPoint(const Ogre::Vector3 &aArrivalPoint)
    {
        _arrivalPoint = aArrivalPoint;
        _distance = _entity->getParentSceneNode()->getPosition().distance(_arrivalPoint);

        if (std::abs(_arrivalPoint.x - _entity->getParentSceneNode()->getPosition().x)
            == (_mapSize.first - 1) * MAP_OFFSET) {
            _willTeleport = true;
        }
        if (std::abs(_arrivalPoint.z - _entity->getParentSceneNode()->getPosition().z)
            == (_mapSize.second - 1) * MAP_OFFSET) {
            _willTeleport = true;
        }
    }

    void MovementHandler::updateMovement(Ogre::Real aTimeSinceLastFrame, int aServerSpd)
    {
        auto myPos = _entity->getParentSceneNode()->getPosition();
        Ogre::Real myMoveSpd = aServerSpd * aTimeSinceLastFrame;

        if (_willTeleport) {
            return;
        }

        _distance -= myMoveSpd;
        if (_distance <= 0) {
            _entity->getParentSceneNode()->setPosition(_arrivalPoint.x, PLAYER_Y_POS, _arrivalPoint.z);
            _arrivalPoint = Ogre::Vector3::ZERO;
            return;
        }
        auto myDir = _arrivalPoint - myPos;
        myDir.normalise();
        myDir *= myMoveSpd;
        _entity->getParentSceneNode()->translate(myDir);
    }

    bool MovementHandler::isMoving() const
    {
        return _arrivalPoint != Ogre::Vector3::ZERO;
    }

    bool MovementHandler::willTeleport() const
    {
        return _willTeleport;
    }

    void MovementHandler::teleport()
    {
        _entity->getParentSceneNode()->setPosition(_arrivalPoint.x, PLAYER_Y_POS, _arrivalPoint.z);
        _arrivalPoint = Ogre::Vector3::ZERO;

        _willTeleport = false;
    }
} // namespace Zappy::GUI