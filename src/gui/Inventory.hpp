//
// Created by beafowl on 12/06/23.
//

#ifndef TESTING_CMAKE_INVENTORY_HPP
#define TESTING_CMAKE_INVENTORY_HPP

#include <OGRE/Overlay/OgreFont.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreTechnique.h>
#include <OGRE/OgreTextureManager.h>
#include "Inventory.hpp"
#include "Constexpr.hpp"
#include "ItemPacket.hpp"
#include "ClientApi.hpp"

namespace Zappy::GUI {
    class Inventory {
    public:
        Inventory();
        ~Inventory() = default;

        void CreateMaterial(const std::string &aPath);
        Ogre::OverlayContainer *CreateMaterial(const std::string &aName, const std::string &aPath, Ogre::OverlayContainer *aContainer, Ogre::Vector2 aPosition, Ogre::Vector2 aDimensions);
        int parsePlayer(const std::string &aString);
        void displayPlayerInventory(int aId, ClientApi &aClientApi);
        ItemPacket getInventoryPlayer(int aId, ClientApi &aClientApi);

    private:
        int _food;
        int _linemate;
        int _deraumere;
        int _sibur;
        int _mendiane;
        int _phiras;
        int _thystame;
    };
}

#endif // TESTING_CMAKE_INVENTORY_HPP
