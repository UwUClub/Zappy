//
// Created by beafowl on 12/06/23.
//

#include <OGRE/Overlay/OgreFont.h>
#include "Inventory.hpp"
#include "Constexpr.hpp"
#include "SceneBuilder.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    Inventory::Inventory(App &aApp) : _app(aApp)
    {}

    int Inventory::parsePlayer(const std::string &aString)
    {
        if (aString.find("Player_") != std::string::npos) {
            std::string myNumber = aString.substr(aString.find("Player_") + 7);
            return std::stoi(myNumber);
        }
        return -1;
    }

    std::pair<int, int> Inventory::parseTile(const std::string &aString)
    {
        std::istringstream myFile(aString);
        int myX = 0;
        int myY = 0;

        myFile >> myX >> myY;
        return std::make_pair(myX, myY);
    }

    void Inventory::displayPlayerInventory(int aId, App &aApp)
    {
        auto myPlayerData = std::find_if(aApp.getServerData()._players.begin(), aApp.getServerData()._players.end(),
                                         [&aId](const PlayerData &aPlayer) {
                                             return std::stoi(aPlayer.getId()) == aId;
                                         });
        _id = stoi(myPlayerData->getId());
        _pos = myPlayerData->getPosition();
        ItemPacket myInventory = myPlayerData->getAllInventory();

        std::string InventoryOverlay =
            "Inventory of the player " + std::to_string(aId) + "\nFood: " + std::to_string(myInventory._food)
            + "\nLinemate: " + std::to_string(myInventory._linemate) + "\nDeraumere: "
            + std::to_string(myInventory._deraumere) + "\nSibur: " + std::to_string(myInventory._sibur) + "\nMendiane: "
            + std::to_string(myInventory._mendiane) + "\nPhiras: " + std::to_string(myInventory._phiras)
            + "\nThystame: " + std::to_string(myInventory._thystame);

        SceneBuilder::createText(INVENTORY_OVERLAY, InventoryOverlay, "Inventory", Ogre::Vector2(1400, 20), Ogre::Vector2(500, 195),"Inventory.png", RESSOURCE_GROUP_NAME, Ogre::Vector2(45, 15));
    }

    void Inventory::displayTilesInventory(std::pair<int, int> aPos, App &aApp)
    {
        auto myTileData = std::find_if(aApp.getServerData()._mapTiles.cbegin(), aApp.getServerData()._mapTiles.cend(),
                                       [&aPos](const TileContent &aTile) {
                                           return aTile._x == static_cast<unsigned int>(aPos.first) && aTile._y == static_cast<unsigned int>(aPos.second);
                                       });
        auto myInventory = myTileData->_items;

        std::string InventoryOverlay =
            "Inventory of the tile " + std::to_string(aPos.first) + ", " + std::to_string(aPos.second) + "\nFood: "
            + std::to_string(myInventory._food) + "\nLinemate: " + std::to_string(myInventory._linemate)
            + "\nDeraumere: " + std::to_string(myInventory._deraumere) + "\nSibur: " + std::to_string(myInventory._sibur)
            + "\nMendiane: " + std::to_string(myInventory._mendiane) + "\nPhiras: " + std::to_string(myInventory._phiras)
            + "\nThystame: " + std::to_string(myInventory._thystame);

        SceneBuilder::createText(INVENTORY_OVERLAY, InventoryOverlay, "Inventory", Ogre::Vector2(1400, 20), Ogre::Vector2(500, 195),"Inventory.png", RESSOURCE_GROUP_NAME, Ogre::Vector2(45, 15));
    }

    void Inventory::switchDisplayedPlayer()
    {
        auto myPlayer = std::find_if(_app.getServerData()._players.cbegin(), _app.getServerData()._players.cend(),
                                     [this](const PlayerData &aPlayer) {
                                         return std::stoi(aPlayer.getId()) != _id && aPlayer.getPosition() == _pos;
                                     });

        if (myPlayer != _app.getServerData()._players.cend()) {
            displayPlayerInventory(std::stoi(myPlayer->getId()), const_cast<App &>(_app));
        }
    }

} // namespace Zappy::GUI