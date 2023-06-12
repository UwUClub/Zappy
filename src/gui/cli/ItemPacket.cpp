/*
** EPITECH PROJECT, 2023
** zap
** File description:
** ItemPacket
*/

#include "ItemPacket.hpp"
#include <functional>
#include <unordered_map>

namespace Zappy::GUI {

    void ItemPacket::fillItemPacket(std::vector<int> &aItemPacketData)
    {
        _food = aItemPacketData[Ressources::FOOD];
        _linemate = aItemPacketData[Ressources::LINEMATE];
        _deraumere = aItemPacketData[Ressources::DERAUMERE];
        _sibur = aItemPacketData[Ressources::SIBUR];
        _mendiane = aItemPacketData[Ressources::MENDIANE];
        _phiras = aItemPacketData[Ressources::PHIRAS];
        _thystame = aItemPacketData[Ressources::THYSTAME];
    }

    void ItemPacket::addResources(int aA)
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

        if (myInventoryMap.find(aA) == myInventoryMap.end()) {
            return;
        }
        myInventoryMap.at(aA)();
    }

    void ItemPacket::removeResources(int aA)
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

        if (myInventoryMap.find(aA) == myInventoryMap.end()) {
            return;
        }
        myInventoryMap.at(aA)();
    }
} // namespace Zappy::GUI