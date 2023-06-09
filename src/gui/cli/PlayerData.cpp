#include "PlayerData.hpp"
#include <utility>

namespace Zappy::GUI {
    PlayerData::PlayerData(std::string aId)
        : _position(std::make_pair(0, 0)),
          _id(std::move(aId))
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

    void PlayerData::setOrientation(int aOrientation)
    {
        if (aOrientation > 4 || aOrientation < 1) {
            return;
        }
        _orientation = static_cast<Orientation>(aOrientation);
    }

    void PlayerData::setLevel(int aLevel)
    {
        _level = aLevel;
    }

    void PlayerData::setInventory(ItemPacket &aInventory)
    {
        _inventory = aInventory;
    }

    void PlayerData::setInventory(int aSlot, int aQuantity)
    {
        static const std::unordered_map<int, std::function<void(ItemPacket &, int)>> myInventoryMap = {
            {0,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._food = aQuant;
             }},
            {1,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._linemate = aQuant;
             }},
            {2,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._deraumere = aQuant;
             }},
            {3,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._sibur = aQuant;
             }},
            {4,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._mendiane = aQuant;
             }},
            {5,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._phiras = aQuant;
             }},
            {6, [](ItemPacket &aInventory, int aQuant) {
                 aInventory._thystame = aQuant;
             }}};
        if (myInventoryMap.find(aSlot) == myInventoryMap.end()) {
            return;
        }
        myInventoryMap.at(aSlot)(_inventory, aQuantity);
    }

    void PlayerData::setTeamName(std::string aTeamName)
    {
        _teamName = std::move(aTeamName);
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

    int PlayerData::getInventory(int aSlot) const
    {
        static const std::unordered_map<int, std::function<int(ItemPacket)>> myInventoryMap = {
            {0,
             [](ItemPacket aInventory) {
                 return aInventory._food;
             }},
            {1,
             [](ItemPacket aInventory) {
                 return aInventory._linemate;
             }},
            {2,
             [](ItemPacket aInventory) {
                 return aInventory._deraumere;
             }},
            {3,
             [](ItemPacket aInventory) {
                 return aInventory._sibur;
             }},
            {4,
             [](ItemPacket aInventory) {
                 return aInventory._mendiane;
             }},
            {5,
             [](ItemPacket aInventory) {
                 return aInventory._phiras;
             }},
            {6, [](ItemPacket aInventory) {
                 return aInventory._thystame;
             }}};
        if (myInventoryMap.find(aSlot) == myInventoryMap.end()) {
            return -1;
        }
        return myInventoryMap.at(aSlot)(_inventory);
    }

    ItemPacket PlayerData::getAllInventory()
    {
        return _inventory;
    }

    const std::string &PlayerData::getTeamName() const
    {
        return _teamName;
    }

    const std::string &PlayerData::getId() const
    {
        return _id;
    }
}; // namespace Zappy::GUI
