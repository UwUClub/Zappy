/*
** EPITECH PROJECT, 2023
** zap
** File description:
** AnimationHandler
*/

#include "AnimationHandler.hpp"
#include <OgreAnimationState.h>
#include <iostream>

namespace Zappy::GUI {
    AnimationHandler::AnimationHandler(Ogre::Entity *aEntity)
        : _entity(aEntity)
    {}

    AnimationHandler::~AnimationHandler()
    {
        for (const auto &animationState : _animationNames) {
            try {
                auto *myAnim = _entity->getAnimationState(animationState);

                if (myAnim == nullptr || !myAnim->getEnabled()) {
                    continue;
                }

                myAnim->setEnabled(false);
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void AnimationHandler::addAnimation(const std::string &aAnimationName, bool aLoop)
    {
        try {
            auto *myAnim = _entity->getAnimationState(aAnimationName);

            _animationNames.emplace(aAnimationName);
            myAnim->setLoop(aLoop);
            myAnim->setEnabled(true);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void AnimationHandler::removeAnimation(const std::string &aAnimationName)
    {
        try {
            auto *myAnim = _entity->getAnimationState(aAnimationName);

            _animationNames.erase(aAnimationName);
            myAnim->setEnabled(false);
            myAnim->setTimePosition(0);
            myAnim->setLoop(false);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void AnimationHandler::updateAnimation(Ogre::Real aTimeSinceLastFrame)
    {
        for (const auto &animationName : _animationNames) {
            auto *myAnim = _entity->getAnimationState(animationName);

            if (!myAnim->getEnabled()) {
                continue;
            }

            myAnim->addTime(aTimeSinceLastFrame);
        }
    }

    void AnimationHandler::stopAnimation(const std::string &aAnimationName)
    {
        try {
            auto *myAnim = _entity->getAnimationState(aAnimationName);

            myAnim->setEnabled(false);
            myAnim->setTimePosition(0);
            myAnim->setLoop(false);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
} // namespace Zappy::GUI
