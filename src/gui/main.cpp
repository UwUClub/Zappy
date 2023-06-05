//
// Created by beafowl on 22/05/23.
//

#include <OgreRenderWindow.h>
#include <thread>
#include "App.hpp"
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main(int argc, char **argv)
{
    try {
        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
        parserData.parseData(argc, argv);
        Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
        myClientApi.joinGame();
        std::thread myCliThread(&Zappy::GUI::ClientApi::run, &myClientApi);
        Zappy::GUI::App ctx(myClientApi, "Zappy");
        // map size | map content | teams | time unit | player connected
        ctx.getRoot()->startRendering();
        std::cout << "End of rendering" << std::endl;
        myCliThread.join();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
