//
// Created by beafowl on 22/05/23.
//

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include "App.hpp"

int main()
{
    Zappy::GUI::App app;
    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Hello, World!" << std::endl;
    return EXIT_SUCCESS;
}