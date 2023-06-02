#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"

namespace Zappy::GUI {

    class Player;

    struct Tile
    {
        unsigned int _x;
        unsigned int _y;
        ItemPacket _items;
    };

    struct ServerData
    {
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<Tile> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<Player> _players;
            int _timeUnit;
    };
} // namespace Zappy::GUI
