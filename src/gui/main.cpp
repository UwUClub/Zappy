//
// Created by beafowl on 22/05/23.
//

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    try {
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
