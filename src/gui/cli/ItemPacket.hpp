#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace Zappy::GUI {
    class ItemPacket
    {
        public:
            ItemPacket() = default;
            ~ItemPacket() = default;

            void fillItemPacket(std::vector<int> &aItemPacketData)
            {
                _food = aItemPacketData[0];
                _linemate = aItemPacketData[1];
                _deraumere = aItemPacketData[2];
                _sibur = aItemPacketData[3];
                _mendiane = aItemPacketData[4];
                _phiras = aItemPacketData[5];
                _thystame = aItemPacketData[6];
            };

            void addResources(int a)
            {
                static const std::unordered_map<int, std::function<void()>> myInventoryMap = {{0,
                                                                                               [this]() {
                                                                                                   _food++;
                                                                                               }},
                                                                                              {1,
                                                                                               [this]() {
                                                                                                   _linemate++;
                                                                                               }},
                                                                                              {2,
                                                                                               [this]() {
                                                                                                   _deraumere++;
                                                                                               }},
                                                                                              {3,
                                                                                               [this]() {
                                                                                                   _sibur++;
                                                                                               }},
                                                                                              {4,
                                                                                               [this]() {
                                                                                                   _mendiane++;
                                                                                               }},
                                                                                              {5,
                                                                                               [this]() {
                                                                                                   _phiras++;
                                                                                               }},
                                                                                              {6, [this]() {
                                                                                                   _thystame++;
                                                                                               }}};

                if (myInventoryMap.find(a) == myInventoryMap.end()) {
                    return;
                }
                myInventoryMap.at(a)();
            }

            void removeResources(int a)
            {
                static const std::unordered_map<int, std::function<void()>> myInventoryMap = {{0,
                                                                                               [this]() {
                                                                                                   _food--;
                                                                                               }},
                                                                                              {1,
                                                                                               [this]() {
                                                                                                   _linemate--;
                                                                                               }},
                                                                                              {2,
                                                                                               [this]() {
                                                                                                   _deraumere--;
                                                                                               }},
                                                                                              {3,
                                                                                               [this]() {
                                                                                                   _sibur--;
                                                                                               }},
                                                                                              {4,
                                                                                               [this]() {
                                                                                                   _mendiane--;
                                                                                               }},
                                                                                              {5,
                                                                                               [this]() {
                                                                                                   _phiras--;
                                                                                               }},
                                                                                              {6, [this]() {
                                                                                                   _thystame--;
                                                                                               }}};

                if (myInventoryMap.find(a) == myInventoryMap.end()) {
                    return;
                }
                myInventoryMap.at(a)();
            }

            int _food {0};
            int _linemate {0};
            int _deraumere {0};
            int _sibur {0};
            int _mendiane {0};
            int _phiras {0};
            int _thystame {0};
    };
} // namespace Zappy::GUI
