/*
** EPITECH PROJECT, 2023
** zap
** File description:
** AnimationHandler
*/

#ifndef ANIMATIONHANDLER_HPP_
#define ANIMATIONHANDLER_HPP_

#include <OgreEntity.h>
#include <OgrePrerequisites.h>
#include <string>
#include <vector>
namespace Zappy::GUI {
    /**
     * @brief Handle the animations
     */
    class AnimationHandler final
    {
        public:
            /**
             * @brief Construct a new Animation Handler object
             *
             */
            explicit AnimationHandler(Ogre::Entity *aEntity);
            /**
             * @brief Destroy the Animation Handler object
             *
             */
            ~AnimationHandler();

            /**
             * @brief Add an animation to the handler
             *
             * @param animationName the name of the animation to play
             */
            void addAnimation(const std::string &aAnimationName, bool aLoop = true);

            /**
             * @brief Remove an animation from the handler
             *
             * @param aAnimationName the name of the animation to remove
             */
            void removeAnimation(const std::string &aAnimationName);

            /**
             * @brief Stop an animation
             *
             * @param aAnimationName the name of the animation to stop
             */
            void stopAnimation(const std::string &aAnimationName);

            /**
             * @brief Update the time
             *
             * @param aTimeSinceLastFrame the time since the last frame
             */
            void updateAnimation(Ogre::Real aTimeSinceLastFrame);

        private:
            std::set<std::string> _animationNames;
            Ogre::Entity *_entity;
    };
} // namespace Zappy::GUI

#endif /* !ANIMATIONHANDLER_HPP_ */
