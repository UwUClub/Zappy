#include "Player.hpp"

namespace Zappy::GUI {

    Player::Player()
    {
        std::cout << "put02" << std::endl;
        _position = std::make_pair(0, 0);
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

    void Player::setInventory(ItemPacket &aInventory)
    {
        std::cout << "put1" << std::endl;
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

    int Player::getInventory(long unsigned int aSlot) const
    {
        switch (aSlot) {
            case 0:
                return _inventory._food;
            case 1:
                return _inventory._linemate;
            case 2:
                return _inventory._deraumere;
            case 3:
                return _inventory._sibur;
            case 4:
                return _inventory._mendiane;
            case 5:
                return _inventory._phiras;
            case 6:
                return _inventory._thystame;
            default:
                return -1;
        }
    }

    ItemPacket Player::getAllInventory()
    {
        return _inventory;
    }
}; // namespace Zappy::GUI
