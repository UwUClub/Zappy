#include "Player.hpp"
#include <utility>

namespace Zappy::GUI {

    Player::Player()
    {
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

    void Player::setOrientation(int aOrientation)
    {
        if (aOrientation > 4 || aOrientation < 1) {
            return;
        }
        _orientation = static_cast<Orientation>(aOrientation - 1);
    }

    void Player::setLevel(int aLevel)
    {
        _level = aLevel;
    }

    void Player::setInventory(ItemPacket &aInventory)
    {
        _inventory = aInventory;
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

    int Player::getInventory(int aSlot) const
    {
        static const std::unordered_map<int, std::function<int (ItemPacket)>> myInventoryMap = {
                {0, [](ItemPacket aInventory) { return aInventory._food; }},
                {1, [](ItemPacket aInventory) { return aInventory._linemate; }},
                {2, [](ItemPacket aInventory) { return aInventory._deraumere; }},
                {3, [](ItemPacket aInventory) { return aInventory._sibur; }},
                {4, [](ItemPacket aInventory) { return aInventory._mendiane; }},
                {5, [](ItemPacket aInventory) { return aInventory._phiras; }},
                {6, [](ItemPacket aInventory) { return aInventory._thystame; }}
            };
        if (myInventoryMap.find(aSlot) == myInventoryMap.end()) {
            return -1;
        }
        return myInventoryMap.at(aSlot)(_inventory);
    }

    ItemPacket Player::getAllInventory()
    {
        return _inventory;
    }

    std::string Player::getTeamName() const
    {
        return _teamName;
    }
}; // namespace Zappy::GUI
