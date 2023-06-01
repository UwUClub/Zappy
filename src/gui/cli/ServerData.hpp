#pragma once

#include <iostream>
#include <vector>
#include "PlayerData.hpp"

namespace Zappy::GUI {

    class PlayerData;

    class TileContent
    {
        public:
            TileContent() = default;
            ~TileContent() = default;

            void fillTile(std::vector<int> &tileData);

            int _x;
            int _y;
            int _food;
            int _linemate;
            int _deraumere;
            int _sibur;
            int _mendiane;
            int _phiras;
            int _thystame;
    };

    struct ServerData
    {
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<TileContent> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<PlayerData> _players;
            int _timeUnit;
    };
} // namespace Zappy::GUI
