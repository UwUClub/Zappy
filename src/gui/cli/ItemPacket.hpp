#pragma once

#include <functional>
#include <iostream>
#include <vector>

namespace Zappy::GUI {
    enum Ressources : int
    {
        FOOD = 0,
        LINEMATE = 1,
        DERAUMERE = 2,
        SIBUR = 3,
        MENDIANE = 4,
        PHIRAS = 5,
        THYSTAME = 6
    };

    class ItemPacket
    {
        public:
            ItemPacket() = default;
            ~ItemPacket() = default;

            void fillItemPacket(std::vector<int> &aItemPacketData);

            void addResources(int aA);

            void removeResources(int aA);

            int _food {0};
            int _linemate {0};
            int _deraumere {0};
            int _sibur {0};
            int _mendiane {0};
            int _phiras {0};
            int _thystame {0};
    };
} // namespace Zappy::GUI
