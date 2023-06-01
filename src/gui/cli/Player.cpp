#include "Player.hpp"

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
}; // namespace Zappy::GUI
