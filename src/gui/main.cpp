//
// Created by beafowl on 22/05/23.
//

#include <cstdlib>
#include <iostream>
#include "ClientApi.hpp"
#include "ParserData.hpp"
#include <stdexcept>
#include <vulkan/vulkan.h>
#include "App.hpp"

int main()
{

    // try {
    //     Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
    //     parserData.parseData(argc, argv);
    //     Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "team_name");
    //     myClientApi.joinGame();
    //     while (true) {
    //         if (myClientApi.update() >= 1) {
    //             break;
    //         }
    //     }
    // } catch (const std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // }
    // return 0;

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
