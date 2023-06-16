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
        static const std::unordered_map<int, std::function<void()>> myInventoryMap = {{Ressources::FOOD,
                                                                                       [this]() {
                                                                                           _food++;
                                                                                       }},
                                                                                      {Ressources::LINEMATE,
                                                                                       [this]() {
                                                                                           _linemate++;
                                                                                       }},
                                                                                      {Ressources::DERAUMERE,
                                                                                       [this]() {
                                                                                           _deraumere++;
                                                                                       }},
                                                                                      {Ressources::SIBUR,
                                                                                       [this]() {
                                                                                           _sibur++;
                                                                                       }},
                                                                                      {Ressources::MENDIANE,
                                                                                       [this]() {
                                                                                           _mendiane++;
                                                                                       }},
                                                                                      {Ressources::PHIRAS,
                                                                                       [this]() {
                                                                                           _phiras++;
                                                                                       }},
                                                                                      {Ressources::THYSTAME, [this]() {
                                                                                           _thystame++;
                                                                                       }}};

        if (myInventoryMap.find(aA) == myInventoryMap.end()) {
            return;
        }
        myInventoryMap.at(aA)();
    }

    void ItemPacket::removeResources(int aA)
    {
        static const std::unordered_map<int, std::function<void()>> myInventoryMap = {{Ressources::FOOD,
                                                                                       [this]() {
                                                                                           _food--;
                                                                                       }},
                                                                                      {Ressources::LINEMATE,
                                                                                       [this]() {
                                                                                           _linemate--;
                                                                                       }},
                                                                                      {Ressources::DERAUMERE,
                                                                                       [this]() {
                                                                                           _deraumere--;
                                                                                       }},
                                                                                      {Ressources::SIBUR,
                                                                                       [this]() {
                                                                                           _sibur--;
                                                                                       }},
                                                                                      {Ressources::MENDIANE,
                                                                                       [this]() {
                                                                                           _mendiane--;
                                                                                       }},
                                                                                      {Ressources::PHIRAS,
                                                                                       [this]() {
                                                                                           _phiras--;
                                                                                       }},
                                                                                      {Ressources::THYSTAME, [this]() {
                                                                                           _thystame--;
                                                                                       }}};

        if (myInventoryMap.find(aA) == myInventoryMap.end()) {
            return;
        }
        myInventoryMap.at(aA)();
    }
} // namespace Zappy::GUI