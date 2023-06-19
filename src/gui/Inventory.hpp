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
#include "App.hpp"
#include "ClientApi.hpp"
#include "Constexpr.hpp"
#include "Inventory.hpp"
#include "ItemPacket.hpp"
#include "Button.hpp"

namespace Zappy::GUI {
    class Inventory
    {
        public:
            explicit Inventory(App &aApp);
            ~Inventory() = default;

            static int parsePlayer(const std::string &aString);
            static std::pair<int, int> parseTile(const std::string &aString);
            void displayPlayerInventory(int aId, App &aApp);
            void displayTilesInventory(std::pair<int, int> aPos, App &aApp);
            void switchDisplayedPlayer();

        private:
            int _id{};
            std::unique_ptr<Button> _button;
            std::pair<unsigned int, unsigned int> _pos;
            const App &_app;
    };
} // namespace Zappy::GUI

#endif // TESTING_CMAKE_INVENTORY_HPP
