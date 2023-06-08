//
// Created by beafowl on 08/06/23.
//

#ifndef TESTING_CMAKE_EGGDATA_HPP
#define TESTING_CMAKE_EGGDATA_HPP

#include <iostream>

namespace Zappy::GUI {
    class EggData {
        public:
            EggData(int aId, std::pair <int, int> aPosition, std::string aTeamName);
            ~EggData() = default;

            /**
             * @brief return the id of the egg
             * @return int
             */
            [[nodiscard]] int getId() const;

            /**
             * @brief return the position of the egg
             * @return std::pair<int, int>
             */
            [[nodiscard]] std::pair <int, int> getPosition() const;

            /**
             * @brief return the team id of the egg
             * @return int
             */
            [[nodiscard]] std::string getTeamName() const;

        private:
            std::pair <int, int> _position;
            std::string _teamName;
            int _id;
    };
}

#endif //TESTING_CMAKE_EGGDATA_HPP
