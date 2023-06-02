#include "Player.hpp"
#include <utility>

namespace Zappy::GUI {

    Player::Player()
    {
        _position = std::make_pair(0, 0);
        _inventory = {0, 0, 0, 0, 0, 0, 0};
    }

    Player::~Player() = default;

    void Player::setPosition(unsigned int aX, unsigned int aY)
    {
        _position = std::make_pair(aX, aY);
    }

    void Player::setOrientation(Orientation aOrientation)
    {
        _orientation = aOrientation;
    }

    void Player::setOrientation(unsigned long int aOrientation)
    {
        if (aOrientation == 1) {
            _orientation = Orientation::NORTH;
        } else if (aOrientation == 2) {
            _orientation = Orientation::EAST;
        } else if (aOrientation == 3) {
            _orientation = Orientation::SOUTH;
        } else if (aOrientation == 4) {
            _orientation = Orientation::WEST;
        }
    }

    void Player::setLevel(int aLevel)
    {
        _level = aLevel;
    }

    void Player::setInventory(int aItem, long unsigned int aSlot)
    {
        if (aSlot > 6) {
            return;
        }
        _inventory[aSlot] = aItem;
    }

    void Player::setTeamName(std::string aTeamName)
    {
        _teamName = std::move(aTeamName);
    }

    const std::pair<unsigned int, unsigned int> &Player::getPosition() const
    {
        return _position;
    }

    const Orientation &Player::getOrientation() const
    {
        return _orientation;
    }

    int Player::getLevel() const
    {
        return _level;
    }

    int Player::getInventory(long unsigned int aSlot) const
    {
        if (aSlot > 6) {
            return -1;
        }
        return _inventory[aSlot];
    }

    std::string Player::getTeamName() const
    {
        return _teamName;
    }
}; // namespace Zappy::GUI
