//
// Created by beafowl on 22/05/23.
//

#include <iostream>
#include "ClientApi.hpp"

int main(int argc, char **argv)
{
    std::cout << "Hello, world!" << std::endl;
    Zappy::GUI::ClientApi clientApi;
    clientApi.connect();
    return 0;
}
