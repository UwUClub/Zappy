#include "ClientApi.hpp"
#include <iostream>

namespace Zappy::GUI {
ClientApi::ClientApi() {}

void ClientApi::connect() { std::cout << "connect" << std::endl; }
}// namespace Zappy::GUI
