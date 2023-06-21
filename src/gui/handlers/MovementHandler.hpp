/*
** EPITECH PROJECT, 2023
** zap
** File description:
** MovementHandler
*/

#ifndef MOVEMENTHANDLER_HPP_
#define MOVEMENTHANDLER_HPP_

#include <OgreEntity.h>
#include <OgrePrerequisites.h>

namespace Zappy::GUI {
    /**
     * @brief Handle the movement of the entity
     *
     */
    class MovementHandler final
    {
        public:
            /**
             * @brief Construct a new Movement Handler object
             *
             * @param aEntity  The entity to move
             */
            explicit MovementHandler(Ogre::Entity *aEntity, const std::pair<int, int> &aMapSize);
            ~MovementHandler();

            /**
             * @brief Set the Arrival Point object
             *
             * @param aArrivalPoint The arrival point
             */
            void setArrivalPoint(const Ogre::Vector3 &aArrivalPoint);

            /**
             * @brief Update the movement
             *
             * @param aTimeSinceLastFrame The time since the last frame
             */
            void updateMovement(Ogre::Real aTimeSinceLastFrame, int aServerSpd);

            /**
             * @brief Check if the entity is moving
             *
             * @return true
             * @return false
             */
            [[nodiscard]] bool isMoving() const;

            /**
             * @brief Check if the entity will teleport
             *
             * @return true
             * @return false
             */
            [[nodiscard]] bool willTeleport() const;

            /**
             * @brief Teleport the entity
             *
             */
            void teleport();

        private:
            Ogre::Entity *_entity;
            Ogre::Vector3 _arrivalPoint;
            Ogre::Real _distance;
            std::pair<int, int> _mapSize;
            bool _willTeleport;
    };
} // namespace Zappy::GUI
#endif /* !MOVEMENTHANDLER_HPP_ */
