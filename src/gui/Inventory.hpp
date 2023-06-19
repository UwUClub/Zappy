//
// Created by beafowl on 12/06/23.
//

#ifndef TESTING_CMAKE_INVENTORY_HPP
#define TESTING_CMAKE_INVENTORY_HPP

#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreTechnique.h>
#include <OGRE/OgreTextureManager.h>
#include <OGRE/Overlay/OgreFont.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include "ClientApi.hpp"
#include "Constexpr.hpp"
#include "Inventory.hpp"
#include "ItemPacket.hpp"
#include "App.hpp"

namespace Zappy::GUI {
    class Inventory
    {
        public:
            Inventory();
            ~Inventory() = default;

            int parsePlayer(const std::string &aString);
            void displayPlayerInventory(int aId, App &aApp);
            ItemPacket getInventoryPlayer(std::vector<PlayerData>::iterator aPlayerData);

        private:
            int _food;
            int _linemate;
            int _deraumere;
            int _sibur;
            int _mendiane;
            int _phiras;
            int _thystame;
    };
} // namespace Zappy::GUI

#endif // TESTING_CMAKE_INVENTORY_HPP
