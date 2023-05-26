#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"

namespace Zappy::GUI {
    struct ServerData
    {
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<std::vector<std::string>> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<Player> _players;
            int _timeUnit;
    };
} // namespace Zappy::GUI
