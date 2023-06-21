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

    AnimationHandler::~AnimationHandler() = default;

    void AnimationHandler::playAnimation(const std::string &aAnimationName, bool aLoop)
    {
        try {
            if (aAnimationName != "IdleBase" || aAnimationName != "IdleTop") {
                removeAnimation("IdleBase");
                removeAnimation("IdleTop");
            }
            auto *myAnim = _entity->getAnimationState(aAnimationName);

            myAnim->setLoop(aLoop);
            myAnim->setEnabled(true);
            myAnim->setTimePosition(0);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void AnimationHandler::removeAnimation(const std::string &aAnimationName)
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

    void AnimationHandler::updateAnimation(Ogre::Real aTimeSinceLastFrame)
    {
        if (_entity->getAllAnimationStates()->getEnabledAnimationStates().empty()) {
            playAnimation("IdleBase");
            playAnimation("IdleTop");
        }

        for (const auto &myAnim : _entity->getAllAnimationStates()->getAnimationStates()) {
            if (!myAnim.second->getEnabled()) {
                continue;
            }
            if (myAnim.second->hasEnded() && !myAnim.second->getLoop()) {
                removeAnimation(myAnim.second->getAnimationName());
                continue;
            }
            myAnim.second->addTime(aTimeSinceLastFrame);
        }
    }
} // namespace Zappy::GUI
