#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"

namespace Zappy::GUI {

    class Player;

    class Tile {
        public:
            Tile() = default;
            ~Tile() = default;

            void fillTile(std::vector<int> &tileData);
            Tile getTileData();

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
            std::vector<Tile> _mapTiles;
            std::vector<std::string> _teamNames;
            std::vector<Player> _players;
            int _timeUnit;
    };
} // namespace Zappy::GUI
