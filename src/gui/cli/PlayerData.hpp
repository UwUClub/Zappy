#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include "ItemPacket.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class ItemPacket;

    enum class Orientation : int
    {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    class PlayerData
    {
        public:
            /**
             * @brief Player constructor
             */
            explicit PlayerData(std::string aId);

            /**
             * @brief Player destructor
             */
            ~PlayerData();

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
             * @brief Set the orientation of the player
             * @param aOrientation
             */
            void setOrientation(int aOrientation);

            /**
             * @brief Set the level of the player
             * @param aLevel
             */
            void setLevel(int aLevel);

            /**
             * @brief Set the inventory of the player
             * @param aInventory
             */
            void setInventory(ItemPacket &aInventory);

            /**
             * @brief Set the inventory of the player
             * @param aSlot
             */
            void setInventory(int aSlot, int aQuantity);

            /**
             * @brief Set the team name of the player
             * @param aTeamName
             */
            void setTeamName(std::string aTeamName);

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
             * @brief Get the Id object
             *
             * @return const std::string&
             */
            [[nodiscard]] const std::string &getId() const;

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
            [[nodiscard]] int getInventory(int aSlot) const;

            /**
             * @brief Get the inventory of the player
             * @return Tile
             */
            ItemPacket getAllInventory() const;

            /**
             * @brief Get the team name of the player
             * @return std::string
             */
            [[nodiscard]] const std::string &getTeamName() const;

        private:
            // Attributes
            std::pair<unsigned int, unsigned int> _position;
            Orientation _orientation {Orientation::NORTH};
            int _level {1};
            ItemPacket _inventory;
            std::string _teamName;
            std::string _id;
    };
} // namespace Zappy::GUI
