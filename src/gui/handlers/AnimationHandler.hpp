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
             * @param aLoop if the animation should loop
             */
            void playAnimation(const std::string &aAnimationName, bool aLoop = true);

            /**
             * @brief Remove an animation from the handler
             *
             * @param aAnimationName the name of the animation to remove
             */
            void removeAnimation(const std::string &aAnimationName);

            /**
             * @brief Update the time
             *
             * @param aTimeSinceLastFrame the time since the last frame
             */
            void updateAnimation(Ogre::Real aTimeSinceLastFrame);

        private:
            Ogre::Entity *_entity;
    };
} // namespace Zappy::GUI

#endif /* !ANIMATIONHANDLER_HPP_ */
