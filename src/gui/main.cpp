#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <iostream>
#include <utility>
#include "ClientApi.hpp"
#include "ParserData.hpp"

class Test {
public:
    Test(std::string mes) : _mes(std::move(mes)) {}

    std::string _mes;
};

int main(int argc, char **argv)
{
//    try {
//        Zappy::GUI::ParserData parserData("127.0.0.1", 0, "");
//        parserData.parseData(argc, argv);
//        Zappy::GUI::ClientApi myClientApi(parserData.getAddress(), parserData.getPort(), "GRAPHIC");
//        myClientApi.joinGame();
//        while (true) {
//            if (myClientApi.update() >= 1) {
//                break;
//            }
//        }
//    } catch (const std::exception &e) {
//        std::cerr << e.what() << std::endl;
//    }
    std::string mes = "Hello World";
    Test test(mes);
    std::cout << mes << std::endl;
    return 0;
}
