#pragma once

#include <iostream>
#include <vector>
#include "PlayerData.hpp"

namespace Zappy::GUI {

    class PlayerData;

    struct TileContent
    {
            unsigned int _x;
            unsigned int _y;
            ItemPacket _items;
    };

    struct ServerData
    {
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<TileContent> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<PlayerData> _players;
            int _freq;
    };
} // namespace Zappy::GUI
