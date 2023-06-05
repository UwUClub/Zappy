#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"

namespace Zappy::GUI {
    class ItemPacket
    {
        public:
            ItemPacket() = default;
            ~ItemPacket() = default;

            void fillItemPacket(std::vector<int> &itemPacketData)
            {
                _food = itemPacketData[0];
                _linemate = itemPacketData[1];
                _deraumere = itemPacketData[2];
                _sibur = itemPacketData[3];
                _mendiane = itemPacketData[4];
                _phiras = itemPacketData[5];
                _thystame = itemPacketData[6];
            };

            int _food {0};
            int _linemate {0};
            int _deraumere {0};
            int _sibur {0};
            int _mendiane {0};
            int _phiras {0};
            int _thystame {0};
    };
} // namespace Zappy::GUI
