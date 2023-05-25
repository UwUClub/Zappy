#include <iostream>
#include <vector>

enum class Orientation { NORTH, EAST, SOUTH, WEST };

struct ServerData
{
    std::pair<unsigned int, unsigned int> _mapSize;
    std::vector<std::vector<std::string>> _mapTiles;
    std::vector<std::string> _teamNames;
    std::pair<unsigned int, unsigned int> _playerPosition;
    Orientation _playerOrientation;
    int _playerLevel;
    int _playerInventory[7];
    int _timeUnit;
};
