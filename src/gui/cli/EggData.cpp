//
// Created by beafowl on 08/06/23.
//

#include "EggData.hpp"

namespace Zappy::GUI {
    EggData::EggData(int aId, std::pair <int, int> aPosition, std::string aTeamName) : _position(aPosition), _teamName(aTeamName), _id(aId)
    {}

    int EggData::getId() const
    {
        return _id;
    }

    std::pair <int, int> EggData::getPosition() const
    {
        return _position;
    }

    std::string EggData::getTeamName() const
    {
        return _teamName;
    }
}