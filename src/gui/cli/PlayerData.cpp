#include "PlayerData.hpp"

namespace Zappy::GUI {
    PlayerData::PlayerData()
        : _position(std::make_pair(0, 0)),
          _inventory({0, 0, 0, 0, 0, 0, 0})
    {}

    PlayerData::~PlayerData() = default;

    void PlayerData::setPosition(unsigned int aX, unsigned int aY)
    {
        _position = std::make_pair(aX, aY);
    }

    void PlayerData::setOrientation(Orientation aOrientation)
    {
        _orientation = aOrientation;
    }

    void PlayerData::setLevel(int aLevel)
    {
        _level = aLevel;
    }

    void PlayerData::setInventory(int aItem, long unsigned int aSlot)
    {
        if (aSlot > 6) {
            return;
        }
        _inventory[aSlot] = aItem;
    }

    const std::pair<unsigned int, unsigned int> &PlayerData::getPosition() const
    {
        return _position;
    }

    const Orientation &PlayerData::getOrientation() const
    {
        return _orientation;
    }

    int PlayerData::getLevel() const
    {
        return _level;
    }

    int PlayerData::getInventory(long unsigned int aSlot) const
    {
        if (aSlot > 6) {
            return -1;
        }
        return _inventory[aSlot];
    }
}; // namespace Zappy::GUI
