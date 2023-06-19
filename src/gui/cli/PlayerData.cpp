#include "PlayerData.hpp"
#include <utility>
#include "ItemPacket.hpp"

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
            {Ressources::FOOD,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._food = aQuant;
             }},
            {Ressources::LINEMATE,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._linemate = aQuant;
             }},
            {Ressources::DERAUMERE,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._deraumere = aQuant;
             }},
            {Ressources::SIBUR,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._sibur = aQuant;
             }},
            {Ressources::MENDIANE,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._mendiane = aQuant;
             }},
            {Ressources::PHIRAS,
             [](ItemPacket &aInventory, int aQuant) {
                 aInventory._phiras = aQuant;
             }},
            {Ressources::THYSTAME, [](ItemPacket &aInventory, int aQuant) {
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
            {Ressources::FOOD,
             [](ItemPacket aInventory) {
                 return aInventory._food;
             }},
            {Ressources::LINEMATE,
             [](ItemPacket aInventory) {
                 return aInventory._linemate;
             }},
            {Ressources::DERAUMERE,
             [](ItemPacket aInventory) {
                 return aInventory._deraumere;
             }},
            {Ressources::SIBUR,
             [](ItemPacket aInventory) {
                 return aInventory._sibur;
             }},
            {Ressources::MENDIANE,
             [](ItemPacket aInventory) {
                 return aInventory._mendiane;
             }},
            {Ressources::PHIRAS,
             [](ItemPacket aInventory) {
                 return aInventory._phiras;
             }},
            {Ressources::THYSTAME, [](ItemPacket aInventory) {
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
