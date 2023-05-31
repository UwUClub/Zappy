//
// Created by beafowl on 30/05/23.
//

#include "ServerData.hpp"

namespace Zappy::GUI {

    void Tile::fillTile(std::vector<int> &tileData)
    {
        _x = tileData[0];
        _y = tileData[1];
        _food = tileData[2];
        _linemate = tileData[3];
        _deraumere = tileData[4];
        _sibur = tileData[5];
        _mendiane = tileData[6];
        _phiras = tileData[7];
        _thystame = tileData[8];
    }

    Tile Tile::getTileData()
    {
        return *this;
    }
} // namespace Zappy::GUI