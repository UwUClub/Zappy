//
// Created by beafowl on 12/06/23.
//

#include "Inventory.hpp"
#include <OGRE/Overlay/OgreFont.h>
#include "Constexpr.hpp"
#include "SceneBuilder.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    Inventory::Inventory()
    {
        _food = 0;
        _linemate = 0;
        _deraumere = 0;
        _sibur = 0;
        _mendiane = 0;
        _phiras = 0;
        _thystame = 0;
    }

    int Inventory::parsePlayer(const std::string &aString)
    {
        if (aString.find("Player_") != std::string::npos) {
            std::string myNumber = aString.substr(aString.find("Player_") + 7);
            return std::stoi(myNumber);
        }
        return -1;
    }

    void Inventory::displayPlayerInventory(int aId, App &aApp)
    {
        auto myPlayerData = std::find_if(aApp.getServerData()._players.begin(), aApp.getServerData()._players.end(),
                                         [&aId](const PlayerData &aPlayer) {
                                             return std::stoi(aPlayer.getId()) == aId;
                                         });
        ItemPacket myInventory = myPlayerData->getAllInventory();

        std::string InventoryOverlay =
            "Inventory of the player " + std::to_string(aId) + "\nFood: " + std::to_string(myInventory._food)
            + "\nLinemate: " + std::to_string(myInventory._linemate) + "\nDeraumere: "
            + std::to_string(myInventory._deraumere) + "\nSibur: " + std::to_string(myInventory._sibur) + "\nMendiane: "
            + std::to_string(myInventory._mendiane) + "\nPhiras: " + std::to_string(myInventory._phiras)
            + "\nThystame: " + std::to_string(myInventory._thystame);

        SceneBuilder::createText(INVENTORY_OVERLAY, InventoryOverlay, "Inventory", Ogre::Vector2(1000, 0),
                                 Ogre::Vector2(500, 195), "Inventory.png", RESSOURCE_GROUP_NAME, Ogre::Vector2(45, 15));
    }
} // namespace Zappy::GUI