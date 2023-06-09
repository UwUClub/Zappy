#pragma once

#include <iostream>
#include <vector>
#include "EggData.hpp"
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
            static ServerData &getInstance()
            {
                static ServerData instance;
                return instance;
            }
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<TileContent> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<PlayerData> _players;
            std::vector<EggData> _eggs;
            int _freq {0};
    };
} // namespace Zappy::GUI
