#include "Player.hpp"

namespace Zappy::GUI {

    Player::Player()
    {
        _position = std::make_pair(0, 0);
        _orientation = Orientation::NORTH;
        _level = 1;
        _inventory = {0, 0, 0, 0, 0, 0, 0};
    }

    Player::~Player()
    {}

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

    void Player::setInventory(std::vector<int, INVENTORY_SIZE> aInventory)
    {
        _inventory = aInventory;
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

    const std::vector<int, INVENTORY_SIZE> &Player::getInventory() const
    {
        return _inventory;
    }
}; // namespace Zappy::GUI
