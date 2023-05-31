#pragma once

#include <array>
#include <iostream>
#include "ServerData.hpp"

const constexpr int INVENTORY_SIZE = 7;

namespace Zappy::GUI {

    enum class Orientation
    {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    class Player
    {
        public:
            /**
             * @brief Player constructor
             */
            Player();

            /**
             * @brief Player destructor
             */
            ~Player();

            /**
             * @brief Set the position of the player
             * @param aX
             * @param aY
             */
            void setPosition(unsigned int aX, unsigned int aY);

            /**
             * @brief Set the orientation of the player
             * @param aOrientation
             */
            void setOrientation(Orientation aOrientation);

            /**
             * @brief Set the level of the player
             * @param aLevel
             */
            void setLevel(int aLevel);

            /**
             * @brief Set the inventory of the player
             * @param aItem
             * @param aSlot
             */
            void setInventory(int aItem, long unsigned int aSlot);

            /**
             * @brief Get the position of the player
             * @return std::pair<unsigned int, unsigned int>
             */
            [[nodiscard]] const std::pair<unsigned int, unsigned int> &getPosition() const;

            /**
             * @brief Get the orientation of the player
             * @return Orientation
             */
            [[nodiscard]] const Orientation &getOrientation() const;

            /**
             * @brief Get the level of the player
             * @return int
             */
            [[nodiscard]] int getLevel() const;

            /**
             * @brief Get the inventory of the player
             * @param aSlot
             * @return item, -1 if invalid
             */
            [[nodiscard]] int getInventory(long unsigned int aSlot) const;

        private:
            // Attributes
            std::pair<unsigned int, unsigned int> _position;
            Orientation _orientation;
            int _level;
            std::array<int, INVENTORY_SIZE> _inventory;
    };
} // namespace Zappy::GUI
